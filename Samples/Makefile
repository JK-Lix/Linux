CC = gcc
SHDIR = ../common
CFLAGS = -Wall -lpthread -lz -lm -lmysqlclient -I $(SHDIR)

OBJS = master.o $(SHDIR)/common.o

all : pihealthd
	@echo "finish"

pihealthd: $(OBJS)
	$(CC) -o $@ $(CFLAGS) $(OBJS) 


$(OBJS): %.o : %.c
	$(CC) -c $(CFLAGS) $< -o $@


.PHONY: clean 

headers:
	gcc -M master.c > headers
include headers

clean:
	@rm -f *.o pihealthd
	@rm -f $(SHDIR)/common.o
	@echo "Clean Done!"


install: pihealthd install.sh pihealthd.conf.sample
	@test -f /etc/pihealthd.conf || cp pihealthd.conf.sample
