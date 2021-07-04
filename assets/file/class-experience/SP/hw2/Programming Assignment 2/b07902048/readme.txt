1. Execution
    compile: make
    execute: ./bidding_system [host_num] [player_num]
2. Description
    When writing bidding_system.c,
    I found that it is safer to get messages from Host.FIFO by sscanf() rather than read().It is because that two root hosts may write to Host.FIFO at the same time and bidding system may read two messages at the same time and cause errors.
    When writing host.c,
        FILE* object can occur errors if we use it to declare an array.
        Ex: FILE* array[2];
        It's important to close used fds while each loop finish, or it would occur errors when too many fd being opened, then the open table would be full and the progresses may stuck.



