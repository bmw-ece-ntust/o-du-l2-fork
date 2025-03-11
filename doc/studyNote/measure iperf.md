# measure iperf

Start Date: 2024/05/06
Summary: Measuring iperf throughput in monolithic and nFAPI split configurations to analyze performance differences.
Status: Done
Assign: Ming 咚咚 [銘鴻]
Tags: Robert Task

measure iperf throughput in monolithic and clarify why less in nFAPI split (assuming both monolithic and nFAPI are 40MHz, SISO, RFsim)

```c
$ iperf3 -c 192.168.70.135 -B 10.0.0.5 -t 40 -R
Connecting to host 192.168.70.135, port 5201
Reverse mode, remote host 192.168.70.135 is sending
[  5] local 10.0.0.5 port 48361 connected to 192.168.70.135 port 5201
[ ID] Interval           Transfer     Bitrate
[  5]   0.00-1.00   sec  5.76 MBytes  48.3 Mbits/sec
[  5]   1.00-2.00   sec  10.6 MBytes  88.6 Mbits/sec
[  5]   2.00-3.00   sec  9.28 MBytes  77.8 Mbits/sec
[  5]   3.00-4.00   sec  10.1 MBytes  85.0 Mbits/sec
[  5]   4.00-5.00   sec  10.6 MBytes  89.3 Mbits/sec
[  5]   5.00-6.00   sec  11.7 MBytes  98.0 Mbits/sec
[  5]   6.00-7.00   sec  10.7 MBytes  89.9 Mbits/sec
[  5]   7.00-8.00   sec  11.3 MBytes  94.8 Mbits/sec
[  5]   8.00-9.00   sec  10.2 MBytes  85.2 Mbits/sec
[  5]   9.00-10.00  sec  11.3 MBytes  95.1 Mbits/sec
[  5]  10.00-11.00  sec  10.7 MBytes  89.6 Mbits/sec
[  5]  11.00-12.00  sec  11.3 MBytes  94.5 Mbits/sec
[  5]  12.00-13.00  sec  10.5 MBytes  88.5 Mbits/sec
[  5]  13.00-14.00  sec  10.4 MBytes  87.5 Mbits/sec
[  5]  14.00-15.00  sec  7.65 MBytes  64.2 Mbits/sec
[  5]  15.00-16.00  sec  10.9 MBytes  91.3 Mbits/sec
[  5]  16.00-17.00  sec  10.5 MBytes  88.4 Mbits/sec
[  5]  17.00-18.00  sec  10.9 MBytes  91.3 Mbits/sec
[  5]  18.00-19.00  sec  10.3 MBytes  86.1 Mbits/sec
[  5]  19.00-20.00  sec  10.7 MBytes  89.8 Mbits/sec
[  5]  20.00-21.00  sec  10.5 MBytes  88.2 Mbits/sec
[  5]  21.00-22.00  sec  11.2 MBytes  93.6 Mbits/sec
[  5]  22.00-23.00  sec  10.4 MBytes  87.3 Mbits/sec
[  5]  23.00-24.00  sec  10.6 MBytes  89.5 Mbits/sec
[  5]  24.00-25.00  sec  10.2 MBytes  85.3 Mbits/sec
[  5]  25.00-26.00  sec  8.96 MBytes  75.2 Mbits/sec
[  5]  26.00-27.00  sec  7.46 MBytes  62.6 Mbits/sec
[  5]  27.00-28.00  sec  11.0 MBytes  92.4 Mbits/sec
[  5]  28.00-29.00  sec  9.55 MBytes  80.1 Mbits/sec
[  5]  29.00-30.00  sec  10.4 MBytes  87.4 Mbits/sec
[  5]  30.00-31.00  sec  9.71 MBytes  81.5 Mbits/sec
[  5]  31.00-32.00  sec  10.4 MBytes  87.6 Mbits/sec
[  5]  32.00-33.00  sec  9.80 MBytes  82.2 Mbits/sec
[  5]  33.00-34.00  sec  10.6 MBytes  88.7 Mbits/sec
[  5]  34.00-35.00  sec  10.3 MBytes  86.3 Mbits/sec
[  5]  35.00-36.00  sec  10.3 MBytes  86.7 Mbits/sec
[  5]  36.00-37.00  sec  9.85 MBytes  82.6 Mbits/sec
[  5]  37.00-38.00  sec  9.37 MBytes  78.6 Mbits/sec
[  5]  38.00-39.01  sec  8.22 MBytes  68.5 Mbits/sec
[  5]  39.01-40.00  sec  9.79 MBytes  82.6 Mbits/sec
- - - - - - - - - - - - - - - - - - - - - - - - -
[ ID] Interval           Transfer     Bitrate         Retr
[  5]   0.00-40.05  sec   408 MBytes  85.4 Mbits/sec  448             sender
[  5]   0.00-40.00  sec   404 MBytes  84.8 Mbits/sec                  receiver
iperf Done.
```