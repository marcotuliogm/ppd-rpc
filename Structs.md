/**TRABALHO DE PPD 1**/


servidor:
> open\_file -abre arquivos com usuarios cadastrados
> busca\_usuario -lista usuarios
> autenticacao\_usuario - liberar acesso


serv\_usuario:
> criar\_arquivos
> chmod\_arquivos
> > add\_user\_arquivo(usuario, arquivo)

> add\_nota(arquivo, nota)
> editar\_nota

str\_usuario:
> nome
> id
> senha
> arquivos\_user[x](x.md)



str\_file:
> titulo
> data
> hora
> notas[.md](.md)
> permissoes[.md](.md)

str\_nota:
> titulo
> conteudo
> estou\_em\_uso return error

cliente:
> listar\_users
> new\_file
> chmod\_arquivo
> listar\_my\_docs
> listar\_my\_docs\_pos\_data
> exibir\_detalhes
> criar\_nota(documento)
> editar\_nota(file and nota)
> listar\_nota(arquivo nota)
> listar\_all\_note(arquivo)