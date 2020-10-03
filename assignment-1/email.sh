#! /bin/bash

declare -A names
declare -A providers

read num
for i in `seq 1 $num`;
do
  read input 
  name=$(echo $input | cut -d'@' -f 1)
  provider=$(echo $input | cut -d'@' -f 2 | cut -d'.' -f 1)
  (( names[${name}]++ ))
  (( providers[${provider}]++ ))
done

for key in "${!names[@]}"; do
  printf '%s ' "$key"
done | tr " " "\n" | sort | tr "\n" " "
echo

for key in "${!providers[@]}"; do
  printf '%s ' "$key"
done | tr " " "\n" | sort | tr "\n" " "
echo
