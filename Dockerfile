FROM gcc:latest
WORKDIR /app
COPY . .
RUN g++ bancario_master.cpp -o app
EXPOSE 10000
CMD ["./app"]
