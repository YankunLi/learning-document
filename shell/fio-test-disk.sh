#!/bin/bash
set -x
echo $1 $2
raw_device=$1
device_raw_size=$2
run_time=10
io_libaio=libaio
io_depth=32

out_dir=/opt/out_directory
result_file=fio_test_outfile.txt
result_path=$out_dir/$result_file

if [ ! -d $out_dir ]; then
    if [ -f $out_dir ]; then
         echo "${out_dir} cann't be a file!\n"
         return 1
    else
            mkdir -p $out_dir
    fi
fi

if [ ! -f $result_path -a ! -d $result_path ]; then
    touch $result_path || exit 1
fi
echo "" > $result_path


echo "$run_program -filename=$raw_device -direct=1 -iodepth $io_depth -thread -rw=randread -ioengine=$io_libaio -bs=4k -size=$device_raw_size -runtime=$run_time -name=randread4k" >> $result_path
$run_program -filename=$raw_device -direct=1 -iodepth $io_depth -thread -rw=randread -ioengine=$io_libaio -bs=4k -size=$device_raw_size -runtime=$run_time -name=randread4k >> $result_path
echo "$run_program -filename=$raw_device -direct=1 -iodepth $io_depth -thread -rw=randread -ioengine=$io_libaio -bs=8k -size=$device_raw_size  -runtime=$run_time -name=randread8k" >> $result_path
$run_program -filename=$raw_device -direct=1 -iodepth $io_depth -thread -rw=randread -ioengine=$io_libaio -bs=8k -size=$device_raw_size  -runtime=$run_time -name=randread8k >> $result_path

