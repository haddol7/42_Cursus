FROM python:3.11.1

COPY requirements.txt /home/requirements.txt
COPY ./script.sh /home/script.sh

RUN chmod 755 /home/script.sh

EXPOSE 11111

WORKDIR /server

CMD [ "bash", "/home/script.sh" ]
