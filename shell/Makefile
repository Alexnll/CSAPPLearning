# Template
# all: server login.cgi
# LIBS = -lpthread

# server: httpServer.c
# 	gcc $< $(LIBS) -o $@

# login.cgi: login.c
# 	gcc $< -o $@

# clean:
# 	rm server login.cgi

sh: sh_main.c err_control.c eval.c
	gcc $^ -o $@

clean:
	rm sh