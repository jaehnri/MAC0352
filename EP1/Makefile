build:
	gcc -o ep1 src/main.c src/mqtt.c src/util.c src/topic.c -Wall -g -pedantic -Wno-unused-result -fsanitize=address

run: build
	./ep1 8000

build-image:
	docker build -f infra/Dockerfile . -t ep1-joao-henri

run-docker: build-image
	docker run -d --name ep1-joao-henri ep1-joao-henri

kill:
	docker kill ep1-joao-henri && docker rm ep1-joao-henri

logs:
	docker logs -f ep1-joao-henri