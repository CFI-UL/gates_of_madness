# gates_of_madness

## crossbox/

vagrant image to get started on development

already contains the cross-compiler and shits

```
cd crossbox
vagrant up
vagrant ssh
```

then from the vm, `make` will cross-compile, push and run the binary on an openwrt instance running on 192.168.1.1

### trivia

symlinking ld.so.1 to libc.so seemed necessary at runtime of the binairies

`ln -s /lib/libc.so /lib/ld.so.1`
