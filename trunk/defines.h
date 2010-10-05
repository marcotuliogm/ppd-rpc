#ifndef defines_h
#define defines_h

enum ERROR{
	ERR_NOT_CONNECTED = -1,
	ERR_NOT_AUTHENTICATED = -2,
	ERR_NOT_EXIST = -3
};

typedef enum
{
    ITEM1 = 1,
	ITEM2,
	ITEM3,
	ITEM4,
	ITEM5,
	ITEM6,
	ITEM7,
	ITEM8,
	ITEM9,
	ITEM10,
} en_menu;

//! Menu itens struct
typedef struct
{
    en_menu name;
    const char *desc;
} ITENS;

//! Menu itens table
static ITENS MENU[] =
{
    { ITEM1        , "* Criar Documento					"},
    { ITEM2        , "* Abri Documento					"},
    { ITEM3        , "* Meus documentos					"},
    { ITEM4        , "Documentos alterados por data/hora"},
    { ITEM5        , "* Listar Usuarios					"},
    { ITEM6        , "* Exit								"},
    { ITEM7        , NULL},
};

static ITENS MENU_DOCS[] =
{
    { ITEM1        , "* Associar usuario ao documento"},
    { ITEM2        , "* Propriedades do documentos   "},
    { ITEM3        , "* Criar uma nota               "},
    { ITEM4        , "* Editar nota                  "},
    { ITEM5        , "* Exibir nota                  "},
    { ITEM6        , "* Exibir Documento             "},
    { ITEM7        , "* Voltar					   "},
    { ITEM8        , NULL},
};
/*
|-Criar Documento
|-Abri Documento
||-Associar usuário a Documentos
||-Propriedades do documentos
||-Criar uma nota
||-Editar nota
||-Exibir nota
||-Exibir Documento
|-Meus documentos
|-Documentos alterados por data/hora
|-Listar Usuários
*/

#endif
