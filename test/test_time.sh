#!/bin/bash

SERVER_PID=$1
MESSAGE=$(printf '%100s' | tr ' ' 'X')  # Crée une chaîne de 100 'X'

# Mesure le temps d'exécution
time ../client $SERVER_PID "$MESSAGE"