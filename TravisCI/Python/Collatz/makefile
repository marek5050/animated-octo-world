FILES :=                              \
    .gitignore                        \
    .travis.yml                       \
    Collatz.html                      \
    Collatz.log                       \
    Collatz.py                        \
    RunCollatz.py                     \
    RunCollatz.in                     \
    RunCollatz.out                    \
    TestCollatz.py                    \
    TestCollatz.out


all:


check:
	@for i in $(FILES);                                        \
    do                                                        \
        if [ -e $$i ]; then echo "$$i found" ; else touch .failed && echo "$$i NOT FOUND" ; fi \
    done ; \
    if [ -e .failed ]; then exit 1;  fi

clean:
	rm -f .coverage
	rm -f *.pyc
	rm -f Collatz.html
	rm -f Collatz.log
	rm -f RunCollatz.out
	rm -f TestCollatz.out
	rm -rf __pycache__

sync:
	make clean
	@echo `pwd`
	@rsync -r -t -u -v --delete \
    --include "*.in"            \
    --include "*.py"            \
    --include "makefile"        \
    --exclude "*"               \
    . downing@$(CS):cs/cs373/github/python/projects/collatz/

test: RunCollatz.out TestCollatz.out

collatz-tests:
	git clone https://github.com/cs373-summer-2015/collatz-tests.git

html: Collatz.py
	pydoc3 -w Collatz

Collatz.log:
	git log > Collatz.log

RunCollatz.out: RunCollatz.py
	./RunCollatz.py < RunCollatz.in > RunCollatz.out

TestCollatz.out: TestCollatz.py
	coverage run    --branch TestCollatz.py >  TestCollatz.out 2>&1
	coverage report -m                      >> TestCollatz.out


push:
	git config --global user.email "marek.bejda@gmail.com"
	git config --global user.name "Marek5050"
ifeq ($(TRAVIS_BRANCH),dev)
	git remote set-branches --add origin master
	git fetch
	git reset --hard
	git checkout master --force 
	git merge --no-ff --no-edit dev
	git push origin master
else ifeq ("$(wildcard $(.fullyCommited))","")
	touch .fullyCommited
	git add .
	git commit -m "Complete commit"
	git push origin master
endif
