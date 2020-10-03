#! /bin/bash

declare -A depts
declare -A genders
genders[M]=0
genders[F]=0

read records
for i in `seq 1 $records`;
do
  read -a input 
  (( depts[${input[1]}]++ ))
  (( genders[${input[3]}]++ ))
done

echo ${#depts[@]}
echo "${genders[M]} ${genders[F]}"
for key in "${!depts[@]}"; do
  printf '%s %s\n' "$key" "${depts[$key]}"
done | sort -k 2n | tail -n1 | awk '{print $1;}'
