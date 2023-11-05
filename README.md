<h1>Super Trunfo Carros</h1> 

### Tópicos 

[Descrição do projeto](#descrição-do-projeto)

[Pré-requisitos](#pré-requisitos)

[Como rodar o projeto](#como-rodar-o-projeto)

## Descrição do projeto 

<p align="justify">
  Este é um projeto é um trabalho feito com base no pdf, é basicamente um jogo chamado Super Trunfo que é um jogo de cartas em que cada carta tem um conjunto de atributos numéricos. 
  
  Dois ou mais jogadores competem escolhendo atributos de uma carta e aquele que tem o maior atributo vence, levando as cartas dos oponentes. Quem conseguir ficar com todas as cartas do baralho vence.  
</p>  

## Pré-requisitos

Compilador de C++11 ou posterior

## Como rodar o projeto

No terminal, clone o projeto: 

```
$ git clone https://github.com/Xgamer4515/Super-Trunfo-Carros
```

Entre no diretório do Gerador: 

```
$ cd Gerador   
```

Compile o programa:

```
$ g++ *.cpp -o gerador
```

Depois rode o programa

```
$ gerador.exe
```

No menu do gerador, importe as cartas arquivo carros.txt. Caso queria mudar as cartas é só mudar o arquivo carros.txt ou adicionar outro arquivo texto no gerador com o modelo assim:

- Modelo
- Velocidade máxima
- Aceleração
- Potencia
- Torque
- Preço

...

Depois de ter criado o arquivo do baralho volte para o diretório Super Trunfo:   
 
```
$ cd ..
```

Entre no diretório Jogo:
```
$ cd Jogo
```

Compile o projeto:
```
$ g++ *.cpp -o jogo
```

Depois rode o jogo

```
$ jogo.exe
```

## Licença 

Este projeto está licenciado sob a [Licença MIT](LICENSE).