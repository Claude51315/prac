Dart
===

# [Installation](https://www.dartlang.org/install/linux)

```
# Enable HTTPS for apt.
$ sudo apt-get update
$ sudo apt-get install apt-transport-https
# Get the Google Linux package signing key.
$ sudo sh -c 'curl https://dl-ssl.google.com/linux/linux_signing_key.pub | apt-key add -'
# Set up the location of the stable repository.
$ sudo sh -c 'curl https://storage.googleapis.com/download.dartlang.org/linux/debian/dart_stable.list > /etc/apt/sources.list.d/dart_stable.list'
$ sudo apt-get update
```



## Pub tool [activation](https://www.dartlang.org/tools/pub/installing)

This tool is included in dart bin directory

```
# find apt-get package Installation directory
$ dpkg -L dart
# set up env variable PATH
$ export PATH=${PATH}:/usr/lib/dart/bin
# or add the above command to ~/.profile to modify PATH variable permenantly

```
