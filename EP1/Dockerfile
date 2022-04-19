FROM gcc:9.4.0

COPY . /usr/local/lib
WORKDIR /usr/local/lib

EXPOSE 8000

RUN gcc -o ep1 mac0352-servidor-exemplo-ep1.c

CMD ["./ep1", "8000"]