for folder in zombie00/ ;do images=$(find $folder -name "*.png" | sort -n);montage $images -background "#00000000" -alpha on -geometry +1+1 "${folder}tex.png"; done
