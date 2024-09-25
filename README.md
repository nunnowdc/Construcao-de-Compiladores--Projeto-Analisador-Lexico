Relatório com o passo a passo que realizei 

 

 

Tendo como base algumas pesquisas que realizei e o que meus companheiros de grupo haviam realizado em minha ausência, tentei por eu mesmo criar um código capaz de separar o arquivo usado como entrada em duas listas destintas. O primeiro arquivo receberia os tokens e identificadores, já o segundo iria receber justamente os símbolos.  

 

Tendo como base esse meu objetivo, fui para a produção do código. 

 

Etapa 1  

Implementei uma função que retorna um inteiro, seu nome foi “buscaLista”, essa função recebe como parâmetro um caractere, a lista a ser percorrida e o tamanho da lista. Após implementá-la, fiz um teste definindo um caractere específico e alguns caracteres especiais na lista de tokens. Como eu havia planejado, deu certo.   


Etapa 2 

Depois de concluir essa etapa, meu próximo objetivo seria fazer com que o programa recebe de entrada um arquivo e verifique cada caractere do arquivo com a lista de tokens já estabelecida. O arquivo escolhido foi um código padrão em C de printar “Hello World!”. A implementação em si deu certo, entretanto percebi que as quebras de linha ‘\n’ não estavam sendo reconhecidos como parte da lista, mas os espaços em branco ‘   ’ estavam sim sendo considerados como presentes na minha suposta lista de tokens. 

 

Etapa 3 

Para a próxima etapa, decidi mudar o nome da “lista_tokens” para “char_especiais”, uma vez que ela não seria a lista de tokens em si, e sim uma lista auxiliar para ajudar na identificação de tokens. Também defini 100 como “TAMANHO_MAXIMO” e adicionei duas novas listas com tamanho maximo de 100, a primeira se chamada “lista_lexemas” que funcionará como a futura tabela de simbolos, já a segunda foi nomeada como “lista_tokens” que como o próprio nome diz irá armazenar os tokens. 


 

Etapa 4 

Já na etapa 4, percebi que seria uma péssima ideia definir um tamanho máximo para as coisas, uma vez que o tamanho varia dependendo do arquivo usado como entrada, então a etapa 4 foi para corrigir esse erro. Então defini variáveis ponteiro para armazenar valores dinamicamente, e sempre que um novo valor iria ser adicionado, usei a função realloc da biblioteca stdlib.h. Sempre verificando se as “listas” estavam vazias (== NULL) para retornar o erro de alocação. 

 

 

Etapa 5 

Essa próxima etapa foi para corrigir o erro identificado na etapa 2 de que o codigo levava em consideração a quebra de linhas “\n” para formar a lista de tokens e tabela de simbolos, para tal, adicionei uma condição em que apenas  “caractere != '\n'” entrariam nas duas listas. O próximo passo realizado nessa etapa foi de fazer com que o codigo ignorasse os comentários na hora de ler o arquivo. Para implementar esse passo, foi necessário adicionar uma condição em que caso o caratere lido do arquivo fosse uma barra “/”, verificar se o proximo caractere é uma barra ”/” ou um asterisco “*”, pois os comentários são formados por “//” ou “/*”. Caso um desses dois casos fosse identificado, o programa iria ignorar todos os caracteres seguintes até encontrar uma quebra de linha “/n” que seria justamente o fim do comentário. 

 

 

 

 

Etapa 6 

Até então a tabela de símbolos e a lista de tokens estavam recebendo apenas caracteres que não fossem espaços em branco, quebras de linha “\n” ou que fizessem parte de um comentário. Então criei uma variável chamada palavra_buffer com 256 bits de espaço (palavra_buffer[256]). Essa variável iria receber os caracteres lidos até que um char_especial, “\n”, espaço em branco ou início de comentário fosse lido, após um desses ser lido, o código joga o que estiver dentro do buffer para a tabela de símbolos e caso o caractere responsável por parar o preenchimento do buffer for um char_especial, ele é adicionado na lista de tokens, mas se for “\n”, espaço em branco ou início de comentário, será apenas desconsiderado. 

 

 

 

 

 

 

Etapa 7 

Na etapa 7 adicionei um novo array chamado de palavras_reservadas, ele continha todas as palavras reservadas contidas no excel disponibilizado {"int", "float", "char", "boolean", "void", "if", "else", "for", "while", "scanf", "printf", "main", "return"}. Juntamente a isso, adicionei uma função no codigo que verificava se a palavra lida do arquivo era uma das palavras_reservadas. A função se chama “buscaPalavra” e recebe como entrada justamente a string que estava dentro do buffer, a lista a ser percorrida e o tamanho dessa lista. Também adicionei a biblioteca string.h para usar sua função strcpy() já que vou precisar comparar palavras (strings). 

(Então invés do buffer ir direto para lista de símbolos, a string dentro do buffer será comparada com o array palavras_reservadas, se for compatível vai para lista de tokens, se não vai para tabela de simbolos). 

 

 

 

 

Etapa 8 

Etapa 8 foi apenas para gerar os prints no fim do código tanto da tabela de tokens quanto da lista de símbolos. Ambos printavam com o auxílio de um for que percorria todos os termos do array e ia printando. Depois dos prints, também coloquei mais 2 fors para desalocar todos os termos de cada array. 

 

 

 

Etapa 9 

Nesta etapa o objetivo foi de fazer com que os símbolos lidos do buffer fossem verificados para saber se eles são números ou strings.  Dependendo de como eles sejam classificados entrarão na lista de tokens como identificadores (NUM, contador) para números e (ID, contador) para strings. 

 Para pôr isto em prática, importei a biblioteca ctype.h para poder saber o tipo primitivo dos caracteres. Criei uma função chamada is_number() que recebe como parâmetro a palavra do buffer e verifica (através de um for) se ela inteira é composta por números com auxílio da função “isdigit” (função da biblioteca ctype.h que retorna 1/true se o caractere for um digito), caso a string for inteira composta por números a função is_number() retorna 1, se não, a função retorna 0.  

No código, caso is_number() retorne 1, o número irá ser adicionado na tabela de símbolos e o seu token (NUM, contador) na lista de tokens, se retornar 0, a string será adicionada na tabela de simbolos e o seu token (ID, contador) na lista de tokens. 

 

 

 

Etapa 10 

Etapa 10 foi para que o código verificasse se um novo token do tipo NUM ou ID já possui um equivalente na lista de tokens, ou seja, caso o código leia do arquivo um símbolo que já foi lido anteriormente, não será adicionado mais uma vez na tabela de simbolos. 

Para tal, uma função find_symbol() foi adicionada, essa função recebe como parâmetro a própria tabela de símbolos, a quantidade de símbolos adicionados e o novo símbolo que acabou de ser lido. A função possui um for que passa por todos os termos da tabela de símbolos verificando (strcmp()) se o buffer em questão ja existe na tabela. 

 

 

 

Etapa 11 

Essa etapa serviu para classificar os nomes de biblioteca como apenas um (ID, count). Também aproveitei para adicionar um novo vetor chamado vetor_comp[] e uma nova categoria de token, os (COMP, count), neles são inclusos {">=", "<=", "==", "!=", ">", "<"}. 

Já na parte de implementação. Verifiquei se após um ‘<’ ser lido o próximo caractere é diferente de um número ou um espaço em branco, se for diferente, tudo que estiver entre ‘<’ e ‘>’ será considerado um (ID, count). Entretanto, caso o próximo caractere for um número ou espaço em branco, ele seguirá normalmente o código sem passar (continue). 

Para implementar a nova categoria de tokens (COMP, count), foi criada uma função buscaComparador() que recebe como parâmetro um possível comparador, o vetor de comparadores e o tamanho do vetor, essa funcionalidade percorre o vetor de comparadores buscando o último caractere lido.  

Criei um vetor possivel_comp[] juntamente a um if para que se o caractere lido do arquivo fosse ‘>’, ‘<’, ‘=’ ou ‘!’, o código verificasse se o proximo_caractere seria um ‘=’, para formar ‘>=’, ‘<=’, ’==’ ou ‘!=’, se não for um ‘=’ ele devolve o próximo caractere ficando apenas com ‘>’, ‘<’, ‘=’ ou ‘!’ e o add no possivel_comp, mas se o proximo_caractere for sim um ‘=’, ambos serão add no possivel_comp. 

Após definir quem seria o possível comparador, basta jogar o possível comparador na função buscaComparador(), se achado, adiciona o seu token (COMP, count) na lista de tokens e na tabela de símbolos o seu símbolo literal. 

 

 

 

 

Etapa 12 

Classificar alguns caracteres especiais como (ID, count) ex: '.', '#', '@' ou '$'. 

Essa etapa se deve ao fato de que no Excel disponibilizado alguns caracteres ficaram fora da classificação de tokens e não poderiam ser ignorados na leitura do arquivo (Eles precisam ser classificados de alguma forma). 

Nesta etapa, também fiz com que o código reconhecesse && e || como tokens literais. 

Dada a ordem que as coisas acontecem no código, primeiro verifica-se se o caractere é ‘<’ para identificar uma possível biblioteca, se não for, verifica se é ‘ “ ‘ para identificar um possível comentário, se não, verifica se é um número, se não for, é uma palavra, se não for, é um comparador. Caso não seja nenhuma dessas opções, o caractere só pode ser um char_especial, então basta apenas descobrir qual é. 

Adicionam-se condicionais logo após a verificação de comparadores, se o caractere lido pertencer ao vetor char_especiais[] e for um desses:  '.', '#', '@' ou  '$'  o seu (ID, count) entrará na tabela de tokens e seu literal na tabela de símbolos, se o caractere nao for nenhum desses 4, seu token literal será adicionado a tabela de tokens. 

Se por acaso o caractere não pertencer ao vetor char_especias[], só resta ser ‘&’ ou ‘|’. Então o proximo_caractere é lido e uma condicional é feita, caso o caractere seja & e o próximo & ou caractere seja | e o próximo |, ‘&&’ ou ‘||’ será adicionado diretamente na tabela de tokens. Mas se o caractere for diferente do proximo_caractere, seu token (ID, count) é adicionado na tabela de tokens, juntamente ao seu literal na lista de símbolos. 

 

 

 

Etapa 13 

Separar números inteiros dos decimais na tabela de tokens, para isso, criei uma função chamada is_number() que recebia como parâmetro o buffer de palavra lida e uma variável recém-criada chamada decimal, essa função é capaz de identificar se uma determinada string é um número decimal ou não, se for decimal, add o token (NUM_DEC, count) na tabela de tokens e o número literal na lista de símbolos, mas se o número for inteiro, o token add na tabela de de tokens é o (NUM_INT, count) e o número literal na lista de símbolos. Caso a string não fosse um número adicionaria o símbolo e o token do ID em duas devidas listas  

 

Etapa 14 

Essa etapa foi para corrigir como os números eram vistos no código, antes eles recebiam o token (NUM_DEC ou NUM_INT, count) e o seu símbolo era o número literal. Porém na análise léxica os números não vão pra lista de símbolos e seu token é no formato (NUM_DEC ou NUM_INT, número literal). 

Para mudar esse funcionamento, bastou remover a parte do código em que os números eram inseridos na lista de símbolos e mudar o count pelo buffer de palavra (que representa o número). 

 

 

  

 

 

 
