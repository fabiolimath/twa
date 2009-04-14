#!/bin/bash

BIN="./hierarquia"
OUT="hierarquia.out"

################# Use uma das opções abaixo ######################
# PAR=""						# Sintaxe.
# PAR="20"						# Todos os valores default.
PAR="40 -c sample-hierarquia.conf"			# Lê configurações do arquivo.
# PAR="20 1 -s 1"					# Identifica instância e genético.
# PAR="20 -g 10"					# Determina o número de soluções visitadas como 10³.
# PAR="20 1 -s 1 -g 10 -c sample-hierarquia.conf"	# Tudojunto.

$BIN $PAR > $OUT

rm -f $OUT

