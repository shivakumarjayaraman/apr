## Please modify the APR_DIR and APR_UTIL_DIR to the directories where you
## have installed APR and APR_UTIL .. 
## Typically if you build these projects, the libs will be deposited under .libs

## Make sure you add this .libs directory to your LD_LIBRARY_PATH for loading 
## the shared lib at runtime
CC=gcc
APR_DIR=/home/shiva/Code/c/apr-1.7.0
APR_UTIL_DIR=/home/shiva/Code/c/apr-util-1.6.1

CFLAGS=-g -I$(APR_DIR)/include -I$(APR_UTIL_DIR)/include 
LDFLAGS=-L$(APR_DIR)/.libs -lapr-1

.PHONY: clean

clean:
	rm -rf basic pool file fileinfo filelock readdir strings timestuff

%:%.c 
	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@
