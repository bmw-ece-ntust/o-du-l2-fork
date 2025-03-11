# TBS and PDU_length

Start Date: 2024/10/08
Summary: Analysis of TBS and PDU_length with comparisons across different message types and their byte differences.
Status: padding
Assign: Ming 咚咚 [銘鴻]

<aside>
💡

Discovered a new observation, recording it here. about TX_Data **PDU_length and TBS**

</aside>

# OAI

The difference between each is 12 bytes. 

## MSG4

```jsx
[PHY]   TBSize[0]: 129
[PHY]   [TX_Data] pNfapiMsg->PDU_length:141
```

## RAR

```jsx
[PHY]   TBSize[0]: 28
[PHY]   [TX_Data] pNfapiMsg->PDU_length:40
```

## SIB1

```jsx
[PHY]   TBSize[0]: 149
[PHY]   [TX_Data] pNfapiMsg->PDU_length:161
```

# OSC

The difference between each is 0 bytes. 

## MSG4

```jsx
[PHY]   TBSize[0]: 116
[PHY]   [TX_Data] pNfapiMsg->PDU_length:116
```

## RAR

```jsx
[PHY]   TBSize[0]: 11
[PHY]   [TX_Data] pNfapiMsg->PDU_length:11
```

## SIB1

```jsx
[PHY]   TBSize[0]: 129
[PHY]   [TX_Data] pNfapiMsg->PDU_length:129
```