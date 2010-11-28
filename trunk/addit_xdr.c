/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#include "addit.h"

bool_t
xdr_record (XDR *xdrs, record *objp)
{
	register int32_t *buf;

	 if (!xdr_int (xdrs, &objp->first_num))
		 return FALSE;
	 if (!xdr_int (xdrs, &objp->second_num))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_text_t (XDR *xdrs, text_t objp)
{
	register int32_t *buf;

	 if (!xdr_vector (xdrs, (char *)objp, 30,
		sizeof (char), (xdrproc_t) xdr_char))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_data_t (XDR *xdrs, data_t objp)
{
	register int32_t *buf;

	 if (!xdr_vector (xdrs, (char *)objp, 3000,
		sizeof (char), (xdrproc_t) xdr_char))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_vet (XDR *xdrs, vet objp)
{
	register int32_t *buf;

	 if (!xdr_vector (xdrs, (char *)objp, 1000,
		sizeof (int), (xdrproc_t) xdr_int))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_account (XDR *xdrs, account *objp)
{
	register int32_t *buf;

	int i;
	 if (!xdr_int (xdrs, &objp->ind))
		 return FALSE;
	 if (!xdr_vector (xdrs, (char *)objp->login, 30,
		sizeof (char), (xdrproc_t) xdr_char))
		 return FALSE;
	 if (!xdr_vector (xdrs, (char *)objp->password, 30,
		sizeof (char), (xdrproc_t) xdr_char))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_Accounts (XDR *xdrs, Accounts *objp)
{
	register int32_t *buf;

	int i;
	 if (!xdr_vector (xdrs, (char *)objp->user, 30,
		sizeof (account), (xdrproc_t) xdr_account))
		 return FALSE;
	 if (!xdr_int (xdrs, &objp->max_users))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_note (XDR *xdrs, note *objp)
{
	register int32_t *buf;

	 if (!xdr_text_t (xdrs, objp->title))
		 return FALSE;
	 if (!xdr_text_t (xdrs, objp->user_edit))
		 return FALSE;
	 if (!xdr_data_t (xdrs, objp->conteudo))
		 return FALSE;
	 if (!xdr_int (xdrs, &objp->num_link))
		 return FALSE;
	 if (!xdr_int (xdrs, &objp->estou_em_uso))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_file (XDR *xdrs, file *objp)
{
	register int32_t *buf;

	int i;

	if (xdrs->x_op == XDR_ENCODE) {
		 if (!xdr_text_t (xdrs, objp->title))
			 return FALSE;
		 if (!xdr_text_t (xdrs, objp->date))
			 return FALSE;
		 if (!xdr_text_t (xdrs, objp->hour))
			 return FALSE;
		 if (!xdr_vector (xdrs, (char *)objp->notes, 100,
			sizeof (note), (xdrproc_t) xdr_note))
			 return FALSE;
		buf = XDR_INLINE (xdrs, (2 + ( 100 )) * BYTES_PER_XDR_UNIT);
		if (buf == NULL) {
			 if (!xdr_int (xdrs, &objp->tam_note))
				 return FALSE;
			 if (!xdr_vector (xdrs, (char *)objp->permissoes, 100,
				sizeof (int), (xdrproc_t) xdr_int))
				 return FALSE;
			 if (!xdr_int (xdrs, &objp->count_permission))
				 return FALSE;

		} else {
		IXDR_PUT_LONG(buf, objp->tam_note);
		{
			register int *genp;

			for (i = 0, genp = objp->permissoes;
				i < 100; ++i) {
				IXDR_PUT_LONG(buf, *genp++);
			}
		}
		IXDR_PUT_LONG(buf, objp->count_permission);
		}
		 if (!xdr_data_t (xdrs, objp->conteudo_inicial))
			 return FALSE;
		 if (!xdr_int (xdrs, &objp->num_link))
			 return FALSE;
		return TRUE;
	} else if (xdrs->x_op == XDR_DECODE) {
		 if (!xdr_text_t (xdrs, objp->title))
			 return FALSE;
		 if (!xdr_text_t (xdrs, objp->date))
			 return FALSE;
		 if (!xdr_text_t (xdrs, objp->hour))
			 return FALSE;
		 if (!xdr_vector (xdrs, (char *)objp->notes, 100,
			sizeof (note), (xdrproc_t) xdr_note))
			 return FALSE;
		buf = XDR_INLINE (xdrs, (2 + ( 100 )) * BYTES_PER_XDR_UNIT);
		if (buf == NULL) {
			 if (!xdr_int (xdrs, &objp->tam_note))
				 return FALSE;
			 if (!xdr_vector (xdrs, (char *)objp->permissoes, 100,
				sizeof (int), (xdrproc_t) xdr_int))
				 return FALSE;
			 if (!xdr_int (xdrs, &objp->count_permission))
				 return FALSE;

		} else {
		objp->tam_note = IXDR_GET_LONG(buf);
		{
			register int *genp;

			for (i = 0, genp = objp->permissoes;
				i < 100; ++i) {
				*genp++ = IXDR_GET_LONG(buf);
			}
		}
		objp->count_permission = IXDR_GET_LONG(buf);
		}
		 if (!xdr_data_t (xdrs, objp->conteudo_inicial))
			 return FALSE;
		 if (!xdr_int (xdrs, &objp->num_link))
			 return FALSE;
	 return TRUE;
	}

	 if (!xdr_text_t (xdrs, objp->title))
		 return FALSE;
	 if (!xdr_text_t (xdrs, objp->date))
		 return FALSE;
	 if (!xdr_text_t (xdrs, objp->hour))
		 return FALSE;
	 if (!xdr_vector (xdrs, (char *)objp->notes, 100,
		sizeof (note), (xdrproc_t) xdr_note))
		 return FALSE;
	 if (!xdr_int (xdrs, &objp->tam_note))
		 return FALSE;
	 if (!xdr_vector (xdrs, (char *)objp->permissoes, 100,
		sizeof (int), (xdrproc_t) xdr_int))
		 return FALSE;
	 if (!xdr_int (xdrs, &objp->count_permission))
		 return FALSE;
	 if (!xdr_data_t (xdrs, objp->conteudo_inicial))
		 return FALSE;
	 if (!xdr_int (xdrs, &objp->num_link))
		 return FALSE;
	return TRUE;
}
