c:\gbdk\bin\lcc -Wa-l -Wf--debug -Wf-ba0 -c -o save.o save.c
c:\gbdk\bin\lcc -Wa-l -Wl-m -Wf--debug -Wl-j -DUSE_SFR_FOR_REG -c -o main.o main.c
c:\gbdk\bin\lcc -Wa-l -Wl-m -Wf--debug -Wl-j -Wm-yn"1DMARATHON" -Wl-yt0x1b -Wl-yo2 -Wl-ya4 -DUSE_SFR_FOR_REG -o main.gb main.o save.o