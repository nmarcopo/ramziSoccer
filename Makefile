# Makefile for final lab

project: project.cpp
	g++ project.cpp gfxnew.o -lX11 -o project
clean:
	rm project
