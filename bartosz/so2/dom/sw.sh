if [ -L "hihih" ]; then
  full=`greadlink -f hihih`
  if $full | grep "^so2"; then
    echo "$full"
  fi
else
  echo "NIE"
fi
