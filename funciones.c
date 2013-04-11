void imprimir(PGresult *resultado,PGresult *resultado_docente)//Esta funcion fue utilizada para comprobar datos, 
                                                              //pero en el programa en si, no se utiliza. 
                                                              //Imprime datos 
{                                                              
      int tuplas_docente,tuplas,campos,i,j;
	    tuplas=PQntuples(resultado);
		tuplas_docente=PQntuples(resultado_docente);
		campos=PQnfields(resultado);
		printf("Docentes que imparten ingenieria de software\n");
		for(i=0;i<tuplas_docente;i++)
		{
			printf(" %s\n",PQgetvalue(resultado_docente,i,0));
		}
		printf("n°|curso_id|docente_id|nota\n");
		for(i=0;i<tuplas;i++)
		{
			printf("%d ",i);
			for(j=0;j<campos;j++)
			{
				printf("     %s",PQgetvalue(resultado,i,j));
			}
			printf("\n");
		}
}
void promedio(PGresult *resultado,PGresult *resultado_docente)//Esta funcion entrega el valor del promedio 
                                                              //y la desviacion estandar
{
	int tuplas_docente,tuplas,campos,i,j,cont;
	float sumap,sumav;
	
	    tuplas=PQntuples(resultado);
		tuplas_docente=PQntuples(resultado_docente);
		campos=PQnfields(resultado);
		
		for(i=0;i<tuplas_docente;i++)
		{
			cont=0;
			sumap=0;
			sumav=0;
			const char* str=PQgetvalue(resultado_docente,i,0);
			for(j=0;j<tuplas;j++)
			{
				if(!strncmp(str,PQgetvalue(resultado,j,1),3))
				{
					float nota=atof(PQgetvalue(resultado,j,2));
					sumap=sumap+nota;
					sumav=sumav+(nota*nota);
				    cont++;
				    //printf("Contador: %d Docente: %s nota: %f suma: %f\n",cont,PQgetvalue(resultado_docente,i,0),atof(PQgetvalue(resultado,j,2)),sumap);
				}
			}
			float x=sumap/cont;
			float varianza=(sumav-cont*(x*x))/cont;
			printf("Docente: %s promedio: %f suma/cont= %f/%d\n",PQgetvalue(resultado_docente,i,0),x,sumap,cont);
			printf("promedio^2: %f sumav %f Varianza: %f Desviacion Estandar: %f\n",x*x,sumav,varianza,sqrt(varianza));
		}				
}
