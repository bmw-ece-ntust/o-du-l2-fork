# Iperf and RRT

Start Date: 2024/04/19
Summary: The project involves using iperf for network performance testing with a focus on measuring high ping and infrequent data requests.
Status: Done
Assign: Ming 咚咚 [銘鴻]

### If we use `iperf`, we will get high ping and high infrequence `TX_Data.request`

```bash
ping 192.168.70.135 -I oaitun_ue1 
```

```bash
iperf3 -c 192.168.70.135 -B "$oaitun_ue1_ip" -t 15 -R
```

![Untitled](Untitled%203.png)

![Untitled](Untitled%204.png)