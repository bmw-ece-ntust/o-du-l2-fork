# Terminate all of container in NB

Start Date: 2024/06/03
Summary: Terminate all Docker containers in the NB environment.
Status: Done
Assign: 陳奕全

### Stopping and Removing All Containers:

If you also want to remove all stopped containers, you can chain the commands:

1. **Stop all running containers**:
    
    ```bash
    docker stop $(docker ps -q)
    ```
    
    1. **Remove all stopped containers**:
    
    ```bash
    docker rm $(docker ps -a -q)
    ```
    
    This sequence ensures that all containers are first stopped and then removed.
    
    ![Untitled](Untitled%20116.png)