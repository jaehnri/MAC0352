build:
	docker build . -t ep1-joao-henri

run: build
	docker run --name ep1-joao-henri -a STDOUT -p 8000:8000 ep1-joao-henri

kill:
	docker kill ep1-joao-henri && docker rm ep1-joao-henri

logs:
	docker logs -f ep1-joao-henri