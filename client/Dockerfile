FROM node

WORKDIR /usr/src/app

COPY package*.json ./

RUN npm install

ENV SERVER_PORT=8080

COPY . .

EXPOSE 8080
ENTRYPOINT [ "npm", "run", "serve" ]
