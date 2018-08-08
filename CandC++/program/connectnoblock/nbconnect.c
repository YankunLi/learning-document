int redisContextConnectTcp(redisContext *c, const char *addr, int port, struct timeval *timeout) {
    int s;
    int blocking = (c->flags & REDIS_BLOCK);
    struct sockaddr_in sa;

    if ((s = redisCreateSocket(c,AF_INET)) < 0)
        return REDIS_ERR;

    if (redisSetBlocking(c,s,0) != REDIS_OK)
        return REDIS_ERR;

    sa.sin_family = AF_INET;
    sa.sin_port = htons(port);
    if (inet_aton(addr, &sa.sin_addr) == 0) {
        struct hostent *he;
        he = gethostbyname(addr);
        if (he == NULL) {
            __redisSetError(c,REDIS_ERR_OTHER,  sdscatprintf(sdsempty(),"Can't resolve: %s",addr));
            close(s);
            return REDIS_ERR;
        }
        memcpy(&sa.sin_addr, he->h_addr, sizeof(struct in_addr));
    }

    if (connect(s, (struct sockaddr*)&sa, sizeof(sa)) == -1) {
        if (errno == EINPROGRESS && !blocking) {
             /* This is ok. */
        } else {
            if (redisContextWaitReady(c,s,timeout) != REDIS_OK)
                return REDIS_ERR;
        }
    }

    /* Reset socket to be blocking after connect(2). */
    if (blocking && redisSetBlocking(c,s,1) != REDIS_OK)
        return REDIS_ERR;

    if (redisSetTcpNoDelay(c,s) != REDIS_OK)
        return REDIS_ERR;

    c->fd = s;
    c->flags |= REDIS_CONNECTED;
    return REDIS_OK;
}

static int redisContextWaitReady(redisContext *c, int fd, const struct timeval *timeout) {
    struct timeval to;
    struct timeval *toptr = NULL;
    fd_set wfd;
    int err;
    socklen_t errlen;

    /* Only use timeout when not NULL. */
    if (timeout != NULL) {
        to = *timeout;
        toptr = &to;
    }

    if (errno == EINPROGRESS) {
        FD_ZERO(&wfd);
        FD_SET(fd, &wfd);

        if (select(FD_SETSIZE, NULL, &wfd, NULL, toptr) == -1) {
            __redisSetError(c,REDIS_ERR_IO,
                sdscatprintf(sdsempty(), "select(2): %s", strerror(errno)));
            close(fd);
            return REDIS_ERR;
        }

        if (!FD_ISSET(fd, &wfd)) {
            errno = ETIMEDOUT;
            __redisSetError(c,REDIS_ERR_IO,NULL);
            close(fd);
            return REDIS_ERR;
        }

        err = 0;
        errlen = sizeof(err);
        if (getsockopt(fd, SOL_SOCKET, SO_ERROR, &err, &errlen) == -1) {
            __redisSetError(c,REDIS_ERR_IO,
                sdscatprintf(sdsempty(), "getsockopt(SO_ERROR): %s", strerror(errno)));
            close(fd);
            return REDIS_ERR;
        }

        if (err) {
            errno = err;
            __redisSetError(c,REDIS_ERR_IO,NULL);
            close(fd);
            return REDIS_ERR;
        }

        return REDIS_OK;
    }

    __redisSetError(c,REDIS_ERR_IO,NULL);
    close(fd);
    return REDIS_ERR;
}
