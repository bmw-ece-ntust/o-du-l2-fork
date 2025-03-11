# Trace DlPageAlloc

Start Date: 2024/09/09
Summary: Implement and debug the DlPageAlloc process in the scheduling and allocation of downlink pages.
Status: Not started
Assign: 陳奕全

```jsx

```

Which part have page `DlPageAlloc` :

DlPageAlloc

PageDlSch

**schFillPagePdschCfg**

**schProcDlPageAlloc**

**MacProcDlPageAlloc**

Comment out `schProcDlPageAlloc` in `SchProcSlotInd`

→ 
Do not allocate page

Why du still allocate page info for DLtti and TXdata

![image.png](image%2053.png)

```c
   //DLtti
   if(dlSlot->pageAllocInfo)
   {
      printf("DEBUG  ->  Dltti has page info~~~~~~~~~~~~\n");
      /* PDCCH and PDSCH PDU is filled */
      count += 2;
   }

//And Txdata
   if(dlSlot->pageAllocInfo)
   {
      printf("DEBUG  ->  txdata has page info~~~~~~~~~~~~\n");
      count++;
   }
```

Try to comment out `SchProcPagingInd`