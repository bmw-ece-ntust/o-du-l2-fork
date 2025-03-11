# How to make nFAPI in OSC makefile

Start Date: 2024/06/21
Summary: Creating and integrating nFAPI into the OSC makefile for small cell projects.
Status: Done
Assign: 陳奕全

## Master make file:

### Add flag

```makefile
#############################################
# Small Cell Integration
# Add flag to enable the nFAPI function
ifeq ($(NFAPI),YES)
	PLTFRM_FLAGS+=-DNFAPI
endif
#############################################
```

### Add library

```makefile
#############################################
# Small Cell Integration
# The library is needed in nFAPI module
ifeq ($(NFAPI),YES)
	L_OPTS+=-lz
endif
#############################################
```

### make du:

```makefile
# Add nFAPI makefile --> to build the nFAPI module
du:
ifeq ($(NFAPI),YES)
		$(Q)$(MAKE) -j -f $(COM_BUILD_DIR)/nfapi.mak OBJ_DIR=$(OBJ_ROOT)/odu LIB_DIR=$(LIB_ROOT)/odu LOG_DIR=$(LOG_ROOT)/odu CC='$(CC1)'
		$(Q)$(MAKE) -j -f $(COM_BUILD_DIR)/nfapi_common.mak OBJ_DIR=$(OBJ_ROOT)/odu LIB_DIR=$(LIB_ROOT)/odu LOG_DIR=$(LOG_ROOT)/odu CC='$(CC1)'
		$(Q)$(MAKE) -j -f $(COM_BUILD_DIR)/nfapi_vnf.mak OBJ_DIR=$(OBJ_ROOT)/odu LIB_DIR=$(LIB_ROOT)/odu LOG_DIR=$(LOG_ROOT)/odu CC='$(CC1)'
		$(Q)$(MAKE) -j -f $(COM_BUILD_DIR)/nfapi_oai_integration.mak OBJ_DIR=$(OBJ_ROOT)/odu LIB_DIR=$(LIB_ROOT)/odu LOG_DIR=$(LOG_ROOT)/odu CC='$(CC1)'
endif
```

**構建命令 `$(Q)$(MAKE) -j -f $(COM_BUILD_DIR)/nfapi.mak ...`**

- 這些行定義了在條件成立時要執行的命令。每一行命令都調用 `make` 工具，以並行模式（`j` 選項）執行一個特定的 `Makefile`，並傳遞一些變數。
- **`$(Q)`**：
    - 這是一個變數，通常用來控制命令的輸出。如果 `$(Q)` 被定義為空字串，命令行會顯示在輸出中。如果它被定義為 `@`，命令行則不會顯示在輸出中。這有助於控制構建過程的可見性。
- **`$(MAKE)`**：
    - 調用 `make` 工具來執行構建命令。
- **`j`**：
    - 表示並行執行多個任務，加快構建速度。
- **`f $(COM_BUILD_DIR)/nfapi.mak`**：
    - 使用指定的 `Makefile`（如 `nfapi.mak`）來執行構建命令。
- **`OBJ_DIR=$(OBJ_ROOT)/odu LIB_DIR=$(LIB_ROOT)/odu LOG_DIR=$(LOG_ROOT)/odu CC='$(CC1)'`**：
    - 傳遞一些變數到 `Makefile` 中，這些變數可以在 `Makefile` 裡使用：
        - `OBJ_DIR=$(OBJ_ROOT)/odu`：定義目標文件目錄。
        - `LIB_DIR=$(LIB_ROOT)/odu`：定義庫文件目錄。
        - `LOG_DIR=$(LOG_ROOT)/odu`：定義日誌文件目錄。
        - `CC='$(CC1)'`：指定編譯器。
        

### clean du:

```makefile
# Small cell integrationπ
# Add nFAPI makefile --> to clean the nFAPI module
clean_odu: 
ifeq ($(NFAPI),YES)
		$(Q)$(MAKE) -j -f $(COM_BUILD_DIR)/nfapi.mak clean OBJ_DIR=$(OBJ_ROOT)/odu LIB_DIR=$(LIB_ROOT)/odu LOG_DIR=$(LOG_ROOT)/odu CC='$(CC1)'
		$(Q)$(MAKE) -j -f $(COM_BUILD_DIR)/nfapi_common.mak clean OBJ_DIR=$(OBJ_ROOT)/odu LIB_DIR=$(LIB_ROOT)/odu LOG_DIR=$(LOG_ROOT)/odu CC='$(CC1)'
		$(Q)$(MAKE) -j -f $(COM_BUILD_DIR)/nfapi_vnf.mak clean OBJ_DIR=$(OBJ_ROOT)/odu LIB_DIR=$(LIB_ROOT)/odu LOG_DIR=$(LOG_ROOT)/odu CC='$(CC1)'
		$(Q)$(MAKE) -j -f $(COM_BUILD_DIR)/nfapi_oai_integration.mak clean OBJ_DIR=$(OBJ_ROOT)/odu LIB_DIR=$(LIB_ROOT)/odu LOG_DIR=$(LOG_ROOT)/odu CC='$(CC1)'
endif	
```

- **目標 `clean_odu:`**
    - 這一行定義了一個名為 `clean_odu` 的構建目標。當你在命令行中執行 `make clean_odu` 時，這個目標會被觸發。
- **條件判斷 `ifeq ($(NFAPI),YES)`**
    - 這一行檢查變數 `NFAPI` 是否等於 `YES`。如果條件成立，則執行接下來的清理命令；否則，這些命令將被忽略。
- **清理命令 `$(Q)$(MAKE) -j -f $(COM_BUILD_DIR)/nfapi.mak clean ...`**
    - 這些行定義了在條件成立時要執行的清理命令。每一行命令都調用 `make` 工具，以並行模式（`j` 選項）執行一個特定的 `Makefile`，並傳遞一些變數進行清理操作。
    - **`$(Q)`**：
        - 這是一個變數，通常用來控制命令的輸出。如果 `$(Q)` 被定義為空字串，命令行會顯示在輸出中。如果它被定義為 `@`，命令行則不會顯示在輸出中。這有助於控制構建過程的可見性。
    - **`$(MAKE)`**：
        - 調用 `make` 工具來執行清理命令。
    - **`j`**：
        - 表示並行執行多個任務，加快清理速度。
    - **`f $(COM_BUILD_DIR)/nfapi.mak clean`**：
        - 使用指定的 `Makefile`（如 `nfapi.mak`）來執行清理命令。`clean` 是這些 `Makefile` 中的一個目標，用於刪除構建過程中生成的文件。
    - **`OBJ_DIR=$(OBJ_ROOT)/odu LIB_DIR=$(LIB_ROOT)/odu LOG_DIR=$(LOG_ROOT)/odu CC='$(CC1)'`**：
        - 傳遞一些變數到 `Makefile` 中，這些變數可以在 `Makefile` 裡使用：
            - `OBJ_DIR=$(OBJ_ROOT)/odu`：定義目標文件目錄。
            - `LIB_DIR=$(LIB_ROOT)/odu`：定義庫文件目錄。
            - `LOG_DIR=$(LOG_ROOT)/odu`：定義日誌文件目錄。
            - `CC='$(CC1)'`：指定編譯器。
    
    ## Sub-makefile:
    
    ![Untitled](Untitled%20124.png)
    
    - nfapi.mak
    - nfapi_common.mak
    - nfapi_vnf.mak
    - nfapi_oai_integration.mak
    
    ### nfapi
    
    ```makefile
    # This is makefile for open-nFAPI module
    include ../common/rsys_fancy.mak
    include ../common/env.mak
    
    COLOR=$(COLOR_RED)
    
    #PLTFRM_FLAGS+=-DMAX_NUM_CCs=1
    
    SRC_DIR=$(ROOT_DIR)/src/nfapi/open-nFAPI/nfapi/src
    C_SRCS=$(wildcard $(SRC_DIR)/*.c)
    C_OBJS=$(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(C_SRCS))
    
    I_OPTS+=-I$(ROOT_DIR)/src/nfapi/open-nFAPI/common/public_inc
    I_OPTS+=-I$(ROOT_DIR)/src/nfapi/open-nFAPI/nfapi/public_inc
    I_OPTS+=-I$(ROOT_DIR)/src/nfapi/open-nFAPI/nfapi/inc
    
    # # prepare the list of the odu header files
    HDR_FILES+=$(wildcard $(SRC_DIR)/*.[hx])
    
    lib: $(LIB_DIR)/libnfapi.a
    include $(COM_BUILD_DIR)/compile.mak
    
    #-------------------------------------------------------------#
    #Linker macros
    #-------------------------------------------------------------#
    $(LIB_DIR)/libnfapi.a:$(C_OBJS)
    		  @echo -e "Creating Archive $(COLOR) $@ $(REVERT_COLOR)"
    		  $(Q)ar -cr $(LIB_DIR)/libnfapi.a $(C_OBJS)
    
    #-------------------------------------------------------------#
    #Clean macros
    #-------------------------------------------------------------#
    clean:
    		  @echo -e "$(COLOR_RED)Cleaning NFAPI$(REVERT_COLOR)"
    		  $(Q)\rm -f $(LIB_DIR)/libnfapi.a $(C_OBJS) 
    
    #**********************************************************************
    #         End of file
    #**********************************************************************
    ```
    

### nfapi_common

```makefile
# This is makefile for open-nFAPI module
include ../common/rsys_fancy.mak
include ../common/env.mak

COLOR=$(COLOR_RED)

SRC_DIR=$(ROOT_DIR)/src/nfapi/open-nFAPI/common/src
C_SRCS=$(wildcard $(SRC_DIR)/*.c)
C_OBJS=$(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(C_SRCS))

# # prepare the list of the odu header files
HDR_FILES+=$(wildcard $(SRC_DIR)/*.[hx])

I_OPTS+=-I$(ROOT_DIR)/src/nfapi/open-nFAPI/common/public_inc

lib: $(LIB_DIR)/libnfapi_common.a
include $(COM_BUILD_DIR)/compile.mak

#-------------------------------------------------------------#
#Linker macros
#-------------------------------------------------------------#
$(LIB_DIR)/libnfapi_common.a:$(C_OBJS)
		  @echo -e "Creating Archive $(COLOR) $@ $(REVERT_COLOR)"
		  $(Q)ar -cr $(LIB_DIR)/libnfapi_common.a $(C_OBJS)

#-------------------------------------------------------------#
#Clean macros
#-------------------------------------------------------------#
clean:
		  @echo -e "$(COLOR_RED)Cleaning NFAPI_COMMON$(REVERT_COLOR)"
		  $(Q)\rm -f $(LIB_DIR)/libnfapi_common.a $(C_OBJS) 

#**********************************************************************
#         End of file
#**********************************************************************
```

### nfapi_vnf

```makefile
# This is makefile for open-nFAPI module
include ../common/rsys_fancy.mak
include ../common/env.mak

COLOR=$(COLOR_RED)

SRC_DIR=$(ROOT_DIR)/src/nfapi/open-nFAPI/vnf/src
C_SRCS=$(wildcard $(SRC_DIR)/*.c)
C_OBJS=$(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(C_SRCS))

I_OPTS+=-I$(ROOT_DIR)/src/nfapi/oai_integration
I_OPTS+=-I$(ROOT_DIR)/src/nfapi/open-nFAPI/common/public_inc
I_OPTS+=-I$(ROOT_DIR)/src/nfapi/open-nFAPI/nfapi/public_inc
I_OPTS+=-I$(ROOT_DIR)/src/nfapi/open-nFAPI/vnf/public_inc
I_OPTS+=-I$(ROOT_DIR)/src/nfapi/open-nFAPI/vnf/inc

# # prepare the list of the odu header files
HDR_FILES+=$(wildcard $(SRC_DIR)/*.[hx])

lib: $(LIB_DIR)/libnfapi_vnf.a
include $(COM_BUILD_DIR)/compile.mak

#-------------------------------------------------------------#
#Linker macros
#-------------------------------------------------------------#
$(LIB_DIR)/libnfapi_vnf.a:$(C_OBJS)
		  @echo -e "Creating Archive $(COLOR) $@ $(REVERT_COLOR)"
		  $(Q)ar -cr $(LIB_DIR)/libnfapi_vnf.a $(C_OBJS)

#-------------------------------------------------------------#
#Clean macros
#-------------------------------------------------------------#
clean:
		  @echo -e "$(COLOR_RED)Cleaning NFAPI_VNF$(REVERT_COLOR)"
		  $(Q)\rm -f $(LIB_DIR)/libnfapi_vnf.a $(C_OBJS) 

#**********************************************************************
#         End of file
#**********************************************************************
```

### nfapi_oai_integration

```makefile
# This is makefile for open-nFAPI module
include ../common/rsys_fancy.mak
include ../common/env.mak

COLOR=$(COLOR_RED)

SRC_DIR=$(ROOT_DIR)/src/nfapi/oai_integration
C_SRCS=$(wildcard $(SRC_DIR)/*.c)
C_OBJS=$(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(C_SRCS))

I_OPTS+=-I$(ROOT_DIR)/src/nfapi/open-nFAPI/common/public_inc
I_OPTS+=-I$(ROOT_DIR)/src/nfapi/open-nFAPI/nfapi/public_inc
I_OPTS+=-I$(ROOT_DIR)/src/nfapi/open-nFAPI/nfapi/inc
I_OPTS+=-I$(ROOT_DIR)/src/nfapi/open-nFAPI/vnf/public_inc
I_OPTS+=-I$(ROOT_DIR)/src/nfapi/open-nFAPI/vnf/inc
# I_OPTS+=-I$(ROOT_DIR)/src/nfapi/open-nFAPI/pnf/public_inc #no need pnf
# I_OPTS+=-I$(ROOT_DIR)/src/nfapi/open-nFAPI/pnf/inc
I_OPTS+=-I$(ROOT_DIR)/src/nfapi/small_cell_integration/public_inc

# # prepare the list of the odu header files
HDR_FILES+=$(wildcard $(SRC_DIR)/*.[hx])

lib: $(LIB_DIR)/libnfapi_oai_integration.a
include $(COM_BUILD_DIR)/compile.mak

#-------------------------------------------------------------#
#Linker macros
#-------------------------------------------------------------#
$(LIB_DIR)/libnfapi_oai_integration.a:$(C_OBJS)
		  @echo -e "Creating Archive $(COLOR) $@ $(REVERT_COLOR)"
		  $(Q)ar -cr $(LIB_DIR)/libnfapi_oai_integration.a $(C_OBJS)

#-------------------------------------------------------------#
#Clean macros
#-------------------------------------------------------------#
clean:
		  @echo -e "$(COLOR_RED)Cleaning NFAPI_OAI_INTEGRATION$(REVERT_COLOR)"
		  $(Q)\rm -f $(LIB_DIR)/libnfapi_oai_integration.a $(C_OBJS) 

#**********************************************************************
#         End of file
#**********************************************************************
```

## du_app.mak

Add nFAPI header file path fro du_app

```makefile
ifeq ($(NFAPI),YES)
I_OPTS+=-I$(ROOT_DIR)/src/nfapi/open-nFAPI/vnf/public_inc
I_OPTS+=-I$(ROOT_DIR)/src/nfapi/open-nFAPI/nfapi/public_inc
I_OPTS+=-I$(ROOT_DIR)/src/nfapi/open-nFAPI/common/public_inc
I_OPTS+=-I$(ROOT_DIR)/src/nfapi/oai_integration
I_OPTS+=-I$(ROOT_DIR)/src/5gnrmac
endif
```

## mac.mak

Add nFAPI header file path fro mac

```makefile
# ========= small cell integration ========= #
ifeq ($(NFAPI),YES)
I_OPTS+=-I$(ROOT_DIR)/src/nfapi/open-nFAPI/vnf/public_inc
I_OPTS+=-I$(ROOT_DIR)/src/nfapi/open-nFAPI/vnf/inc
I_OPTS+=-I$(ROOT_DIR)/src/nfapi/open-nFAPI/nfapi/public_inc
I_OPTS+=-I$(ROOT_DIR)/src/nfapi/open-nFAPI/common/public_inc
I_OPTS+=-I$(ROOT_DIR)/src/nfapi/oai_integration
I_OPTS+=-I$(ROOT_DIR)/src/nfapi/small_cell_integration/public_inc
endif
# ========================================== #
```

## phy_stub.mak

Add nFAPI header file path fro phy_stub

```makefile
# ========= small cell integration ========= #
ifeq ($(NFAPI),YES)
I_OPTS+=-I$(ROOT_DIR)/src/nfapi/open-nFAPI/vnf/public_inc
I_OPTS+=-I$(ROOT_DIR)/src/nfapi/open-nFAPI/nfapi/public_inc
I_OPTS+=-I$(ROOT_DIR)/src/nfapi/open-nFAPI/common/public_inc
I_OPTS+=-I$(ROOT_DIR)/src/nfapi/oai_integration
endif
# ========================================== #
```

## sch.mak

Add nFAPI header file path fro sch

```makefile
# ========= small cell integration ========= #
ifeq ($(NFAPI),YES)
I_OPTS+=-I$(ROOT_DIR)/src/nfapi/open-nFAPI/vnf/public_inc
I_OPTS+=-I$(ROOT_DIR)/src/nfapi/open-nFAPI/nfapi/public_inc
I_OPTS+=-I$(ROOT_DIR)/src/nfapi/open-nFAPI/common/public_inc
I_OPTS+=-I$(ROOT_DIR)/src/nfapi/oai_integration
endif
# ========================================== #
```

## cm.mak

Add nFAPI header file path fro cm

```makefile
# ========= small cell integration ========= #
ifeq ($(NFAPI),YES)
I_OPTS+=-I$(ROOT_DIR)/src/nfapi/open-nFAPI/vnf/public_inc
I_OPTS+=-I$(ROOT_DIR)/src/nfapi/open-nFAPI/nfapi/public_inc
I_OPTS+=-I$(ROOT_DIR)/src/nfapi/open-nFAPI/common/public_inc
I_OPTS+=-I$(ROOT_DIR)/src/nfapi/oai_integration
endif
# ========================================== #
```

當你在源文件中使用 `#include "header.h"` 時，編譯器會先在這些指定的目錄中尋找 `header.h` 文件，從而保證頭文件的正確引用和編譯過程的順利進行。