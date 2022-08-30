all: build

./node_modules:
	npm install --build-from-source

build: ./node_modules
	./node_modules/.bin/node-pre-gyp build -j max --loglevel=silent

debug: ./node_modules
	./node_modules/.bin/node-pre-gyp build -j max --debug --verbose

clean:
	@rm -rf ./build
	rm -rf lib/binding/
	rm -rf ./node_modules/


test:
	npm test

check: test

.PHONY: test clean build
