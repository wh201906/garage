@echo off
sc stop Spooler
sc start Spooler
sc query Spooler
pause