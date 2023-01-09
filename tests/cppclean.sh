#! /bin/sh
# Root directory to cd into.
dir=$1
excluded="Goon/Entrypoint.hpp|unable to find|static data|ImGui|ReadFromFile"
command="cppclean $dir/goon/src | egrep -Ev '$excluded'"
echo $command
cppcleanlines=$(eval $command '| wc -l')
# Use this to see the command output for debugging
eval $command


if [[ $cppcleanlines -ne 0 ]]
then
  echo "Problem with cppclean command"
  eval $command
  exit 1
else
    exit 0
fi
