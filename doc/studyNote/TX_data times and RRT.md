# TX_data times and RRT

Start Date: 2024/04/18
Summary: Analyzing TX data times and RRT performance metrics using iperf testing.
Status: Done
Assign: 陳奕全

<aside>
👀 When using iperf to generate DL traffic, the number of TX_Data.req requests will increase, leading to higher ping delays.

</aside>

![Untitled](Untitled%20108.png)

```
avril 18 16:51:00 Connecting to host 192.168.70.135, port 5201
avril 18 16:51:00 Reverse mode, remote host 192.168.70.135 is sending
avril 18 16:51:00 [  5] local 10.0.0.2 port 35641 connected to 192.168.70.135 port 5201
avril 18 16:51:01 [ ID] Interval           Transfer     Bitrate
avril 18 16:51:01 [  5]   0.00-1.00   sec   867 KBytes  7.10 Mbits/sec                  
avril 18 16:51:02 [  5]   1.00-2.00   sec  1.41 MBytes  11.8 Mbits/sec                  
avril 18 16:51:03 [  5]   2.00-3.00   sec  1.79 MBytes  15.0 Mbits/sec                  
avril 18 16:51:04 [  5]   3.00-4.00   sec  2.41 MBytes  20.2 Mbits/sec                  
avril 18 16:51:05 [  5]   4.00-5.00   sec  3.11 MBytes  26.1 Mbits/sec                  
avril 18 16:51:06 [  5]   5.00-6.00   sec  3.56 MBytes  29.8 Mbits/sec                  
avril 18 16:51:07 [  5]   6.00-7.00   sec  3.56 MBytes  29.9 Mbits/sec                  
avril 18 16:51:08 [  5]   7.00-8.00   sec  3.60 MBytes  30.2 Mbits/sec                  
avril 18 16:51:09 [  5]   8.00-9.00   sec  3.58 MBytes  30.0 Mbits/sec                  
avril 18 16:51:10 [  5]   9.00-10.00  sec  3.57 MBytes  29.9 Mbits/sec                  
avril 18 16:51:11 [  5]  10.00-11.00  sec  3.51 MBytes  29.5 Mbits/sec                  
avril 18 16:51:12 [  5]  11.00-12.00  sec  3.51 MBytes  29.4 Mbits/sec                  
avril 18 16:51:13 [  5]  12.00-13.00  sec  3.52 MBytes  29.5 Mbits/sec                  
avril 18 16:51:14 [  5]  13.00-14.00  sec  3.49 MBytes  29.3 Mbits/sec                  
avril 18 16:51:16 [  5]  14.00-15.00  sec  3.53 MBytes  29.6 Mbits/sec                  
avril 18 16:51:16 - - - - - - - - - - - - - - - - - - - - - - - - -
avril 18 16:51:16 [ ID] Interval           Transfer     Bitrate         Retr
avril 18 16:51:16 [  5]   0.00-15.05  sec  47.6 MBytes  26.5 Mbits/sec    0             sender
avril 18 16:51:16 [  5]   0.00-15.00  sec  45.0 MBytes  25.2 Mbits/sec                  receiver
avril 18 16:51:16 
avril 18 16:51:16 iperf Done.

```