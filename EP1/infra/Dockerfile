FROM gcc:9.4.0

COPY . /usr/local/lib
WORKDIR /usr/local/lib

EXPOSE 8000

RUN gcc -o ep1 src/main.c src/mqtt.c src/util.c src/topic.c

EXPOSE 1883

CMD ["./ep1", "1883"]
