c=0; mkdir tmp; for i in $(find $1 -name "*.png" | sort -n); do cp $i tmp/$(printf "%04d" $c); ((++c)); done; sgemergeimagetest tmp; rm -r tmp; mv out.png "${1}.png"
