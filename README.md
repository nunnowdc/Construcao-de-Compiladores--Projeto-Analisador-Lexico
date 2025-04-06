**Relatório com o passo a passo que realizei para construir o analisador léxico **

 

 

Para desenvolver esta etapa do processo de compilação, utilizei como referência uma abordagem semelhante à dos separadores de moedas, que são organizados de acordo com o tamanho. Nos separadores, as moedas deslizam por uma rampa repleta de furos que aumentam gradualmente em diâmetro, permitindo que cada moeda permaneça em seu caminho até que reste apenas uma opção. Nessa analogia, os lexemas e caracteres correspondem às moedas, enquanto os furos na rampa representam as condicionais do código.

Minha ideia consiste em que os caracteres especiais ou palavras sejam lidos de um determinado arquivo usado como entrada no código. Em seguida, passarão por uma sequência de condicionais capazes de distinguir e classificar adequadamente cada um deles. 

 

Com base nessa ideia principal, nas pesquisas que realizei e nas contribuições dos meus colegas de grupo, procurei desenvolver um código capaz de separar o conteúdo do arquivo de entrada em duas listas distintas. A primeira lista, denominada tabela de tokens, seria responsável por armazenar os tokens e identificadores, enquanto a segunda, denominada lista de símbolos, ficaria responsável pela coleta dos símbolos. 

 

 

Com base nesse objetivo, iniciei a produção do código. 

 

**Etapa 1 (função de buscar caracteres numa lista)** 

Implementei uma função que retorna um inteiro, seu nome foi “buscaLista” (posteriormente se tornou “buscaCaractere”). Essa função recebe como parâmetro um caractere, a lista a ser percorrida e o tamanho da lista. Após sua implementação, realizei um teste definindo um caractere específico e alguns caracteres especiais na lista de tokens. Como planejado, deu certo.   

 

 

**Etapa 2 (ler os caracteres de um arquivo)** 

Após concluir essa etapa, meu próximo objetivo foi permitir que o programa recebesse como entrada um arquivo, verificando cada caractere em relação à lista de tokens previamente estabelecida. O arquivo selecionado foi um código padrão em C que imprime “Hello World!”. Por mais que a implementação tenha funcionado, notei que as quebras de linha “\n” não estavam sendo reconhecidas como parte da lista, enquanto os espaços em branco ‘  ‘  estavam sendo considerados como elementos da minha lista de tokens. 


 

 

**Etapa 3 (criar lista de lexemas e tabela de tokens)** 

Para a próxima etapa, decidi renomear a “lista_tokens” para “char_especiais”, uma vez que ela não representa a lista de tokens propriamente dita, mas sim uma lista auxiliar para identificar tokens. Além disso, defini o valor 100 como “TAMANHO_MAXIMO” e adicionei duas novas listas, também com tamanho máximo de 100. A primeira, denominada “lista_lexemas”, funcionará como a futura tabela de símbolos, enquanto a segunda, intitulada “tabela_tokens”, será responsável por armazenar os tokens. 


 

**Etapa 4 (alocar os vetores dinamicamente)** 

Na etapa 4, percebi que seria uma péssima ideia definir um tamanho máximo para os vetores, uma vez que o tamanho varia conforme o arquivo de entrada. Portanto, essa etapa foi dedicada à correção desse erro. Para isso, utilizei variáveis ponteiro para alocar valores dinamicamente. Sempre que um novo valor precisava ser adicionado, empreguei a função “realloc” da biblioteca “stdlib.h”, Sempre verificando se os vetores estavam vazios (== NULL) para retornar um erro de alocação, quando necessário. 

 

 

 

**Etapa 5 (ignorar comentários comuns e blocos de comentários)** 

Nesta etapa, busquei corrigir o erro identificado na etapa 2, no qual o código considerava as quebras de linha “\n” ao formar a lista de tokens e a tabela de símbolos. Para resolver isso, adicionei uma condição que garante que apenas (caracteres !=  “\n”) sejam incluídos nas duas listas. 

 

Além disso, o próximo passo foi fazer com que o código ignorasse os comentários durante a leitura do arquivo. Para implementar essa funcionalidade, foi necessário adicionar uma condição que, ao encontrar uma barra (‘/’), verificasse se o próximo caractere era outra barra ‘/’ (comentário comum) ou um asterisco ‘*’ (comentário em bloco), uma vez que os comentários são iniciados por “//” ou “/*”.  

Se um comentário comum for identificado, o programa ignorará todos os caracteres subsequentes até encontrar uma quebra de linha (‘\n’), que indicaria o fim do comentário. 

Se um comentário de bloco for identificado, o programa ignorará todos os caracteres até que um “*/” seja encontrado, sinalizando o fim do comentário em bloco. 

 

 

**Etapa 6 (definir um buffer para armazenar símbolos)** 

Até o momento, a tabela de símbolos e a lista de tokens estavam recebendo apenas caracteres que não eram espaços em branco, quebras de linha (‘\n’) ou caracteres pertencentes a comentários. Para melhorar esse processo, criei uma variável denominada palavra_buffer, com capacidade para armazenar 256 caracteres (palavra_buffer[256]). Essa variável tem a finalidade de acumular os caracteres lidos até que um char_escpecial, uma quebra de linha, um espaço em branco ou o início de um comentário seja detectado. Assim que um desses caracteres for identificado, o conteúdo do buffer é transferido para a tabela de símbolos. Caso o caractere responsável por interromper o preenchimento do buffer seja um char_especial, ele é adicionado à lista de tokens. No entanto, se for uma quebra de linha, um espaço em branco ou o início de um comentário, esses caracteres são simplesmente desconsiderados. 

 

**Etapa 7 (identificar palavras reservadas através do buffer)** 

Na etapa 7, adicionei um novo array denominado palavras_reservadas, que contém todas as palavras reservadas listadas no arquivo Excel disponibilizado: {"int", "float", "char", "boolean", "void", "if", "else", "for", "while", "scanf", "printf", "main", "return"}. 

Além disso, implementei uma função no código chamada “buscaPalavra”, seu objetivo é verificar se a palavra lida do arquivo é uma das palavras_reservadas. Essa função recebe como parâmetro a string contida no buffer, a lista a ser percorrida e o tamanho dessa lista. Para facilitar a comparação de palavras (strings), adicionei a biblioteca string.h, que permite o uso da função strcpy(). 

 

(Então invés do buffer ir direto para lista de símbolos, a string dentro do buffer será comparada com o array palavras_reservadas, se for compatível vai para lista de tokens, se não vai para tabela de simbolos). 

 

 

 

**Etapa 8 (printar lista de símbolos e tabela de tokens)** 

Etapa 8 foi apenas para gerar os prints no fim do código tanto da tabela de tokens quanto da lista de símbolos. Ambos printavam com o auxílio de um for que percorria todos os elementos do array e ia printando. Depois dos prints, também coloquei mais 2 fors para desalocar corretamente todos os elementos de cada array, garantindo a liberação adequada da memória utilizada. 

 

 

 

**Etapa 9 (dividir os símbolos em strings e números)** 

Nesta etapa, o objetivo foi verificar os símbolos lidos do buffer para determinar se eles são números ou strings. Dependendo de como cada símbolo for classificado, ele será inserido na lista de tokens como identificadores: (NUM, contador) para números e (ID, contador) para strings.  

Para pôr isto em prática, importei a biblioteca ctype.h, que permite identificar o tipo primitivo dos caracteres. Criei uma função chamada is_number(), que recebe como parâmetro a palavra do buffer e verifica (através de um for) se a string é inteira composta por numeros. Para essa verificação, utilizei a função isdigit (função da biblioteca ctype.h que retorna 1/true se o caractere for um digito, caso a string for inteira composta por números a função is_number() retorna 1, se não, a função retorna 0). 

No código, se a função is_number() retornar 1, o número será adicionado à tabela de símbolos, e o seu token será registrado na lista de tokens como (NUM, contador). Por outro lado, se a função retornar 0, a string será inserida na tabela de símbolos, e seu token será registrado na lista de tokens como (ID, contador).  

 

 

**Etapa 10 (evitar valores iguais na lista de simbolos)** 

Etapa 10 foi para que o código verificasse se um novo token do tipo NUM ou ID já possui um equivalente na lista de tokens, ou seja, caso o código leia do arquivo um símbolo que já foi lido anteriormente, não será adicionado novamente na tabela de símbolos. 

Para tal, uma função find_symbol() foi adicionada, essa função recebe como parâmetro a própria lista de símbolos, a quantidade de símbolos adicionados e o novo símbolo que acabou de ser lido. A função possui um for que passa por todos os termos da tabela de símbolos verificando com o strcmp() se o buffer em questão já existe na lista de simbolos. 

 

 

 

**Etapa 11 (identificar comparadores e nomes de bibliotecas)** 

Essa etapa serviu para classificar os nomes de biblioteca como apenas um (ID, count). Também aproveitei para adicionar um novo vetor chamado vetor_comp[] e uma nova categoria de token, os (COMP, count), neles são inclusos {">=", "<=", "==", "!=", ">", "<"}. 

Já na parte de implementação. Verifiquei se após um ‘<’ ser lido o próximo caractere é diferente de um número ou um espaço em branco, se for diferente, tudo que estiver entre ‘<’ e ‘>’ será considerado um (ID, count). Entretanto, caso o próximo caractere for um número ou espaço em branco, ele seguirá normalmente o código sem passar (continue). 

Criei um vetor possivel_comp[] juntamente a um if para que caso o caractere lido do arquivo for um ‘>’, ‘<’, ‘=’ ou ‘!’, o código verifique se o proximo_caractere é um ‘=’, para formar ‘>=’, ‘<=’, ’==’ ou ‘!=’, se não for um ‘=’ ele devolve o próximo caractere ficando apenas com ‘>’, ‘<’, ‘=’ ou ‘!’ e o adiciona no possivel_comp, mas se o proximo_caractere for sim um ‘=’, ambos serão adicionados no possivel_comp. 

Após definir quem seria o possível comparador, basta jogar o possível comparador na função buscaComparador(), se achado, adiciona o seu token (COMP, count) na lista de tokens e na tabela de símbolos o seu símbolo literal. 

(buscaComparador()  recebe como parâmetro um possível comparador, o vetor_comp[] e o tamanho do vetor). 

 

 

 

 

**Etapa 12 (classificar caracteres nao char_especiais e &, && ||)** 

Classificar alguns caracteres especiais como (ID, count) ex: '.', '#', '@' ou '$'. 

Essa etapa se deve ao fato de que no Excel disponibilizado alguns caracteres ficaram fora da classificação de tokens e não poderiam ser ignorados na leitura do arquivo (Eles precisam ser classificados de alguma forma). 

Nesta etapa, também fiz com que o código reconhecesse && e || como tokens literais. 

Dada a ordem que as coisas acontecem no código, primeiro verifica-se se o caractere é ‘/‘ ou ‘*’ para identificar um possível comentário, se não for, verifica se  é ‘<’ para identificar uma possível biblioteca, se não, verifica se é uma aspa ‘ “ ‘ para identificar um bloco de texto, se não for, é um número, e se não for, é um comparador. Caso não seja nenhuma dessas opções, o caractere só pode ser um char_especial, então basta apenas descobrir qual é. 

Adicionam-se condicionais logo após a verificação de comparadores, se o caractere lido pertencer ao vetor char_especiais[] e for um desses:  '.', '#', '@' ou  '$'  o seu (ID, count) entrará na tabela de tokens e seu literal na tabela de símbolos, se o caractere nao for nenhum desses 4, seu token literal será adicionado a tabela de tokens. 

Se por acaso o caractere não pertencer ao vetor char_especias[], só resta ser ‘&’ ou ‘|’. Então o proximo_caractere é lido e uma condicional é feita, caso o caractere seja & e o próximo & ou caractere seja | e o próximo |, ‘&&’ ou ‘||’ será adicionado diretamente na tabela de tokens. Mas se o caractere for diferente do proximo_caractere, seu token (ID, count) é adicionado na tabela de tokens, juntamente ao seu literal na lista de símbolos. 

 

 

 

 

**Etapa 13 (separar números em inteiros e decimais)**

Separar números inteiros dos decimais na tabela de tokens, para isso, criei uma função chamada is_number() que recebia como parâmetro o buffer de palavra lida e uma variável recém-criada chamada decimal, essa função é capaz de identificar se uma determinada string é um número decimal ou não, se for decimal, add o token (NUM_DEC, count) na tabela de tokens e o número literal na lista de símbolos, mas se o número for inteiro, o token add na tabela de de tokens é o (NUM_INT, count) e o número literal na lista de símbolos. Caso a string não fosse um número adicionaria o símbolo e o token do ID em duas devidas listas  

 

**Etapa 14 (arrumar o contador dos números)**

Essa etapa foi para corrigir como os números eram vistos no código, antes eles recebiam o token (NUM_DEC ou NUM_INT, count) e o seu símbolo era o número literal. Porém na análise léxica os números não vão pra lista de símbolos e seu token é no formato (NUM_DEC ou NUM_INT, número literal). 

Para mudar esse funcionamento, bastou remover a parte do código em que os números eram inseridos na lista de símbolos e mudar o count pelo buffer de palavra (que representa o número).
