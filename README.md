## CTemplate

Simple bash script to generate a C template.

### Procedures

Follow this steps to make the script run globally in your machine.

```shell
git clone https://github.com/joseareia/ctemplate.git
cd ctemplate
./install.sh
```

### Usage

While executing the script you can pass a directory to store the new template along side with the flag `-p` or just simple run it without any arguments to store in the current directory as follow.


```shell
// Without any arguments
ctemplate

// Without -p flag followed by the path
ctemplate -p /some/random/directory
```

It is possible to activate the flag `-s` which will create a new client-server template: `ctemplate -s`.

If any doubts, just run `ctemplate -h` for some brief help.
