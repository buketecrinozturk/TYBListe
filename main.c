#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <stdbool.h>


/*****************struct olu�turuyoruz *********************/ //buketecrinozturk
	struct node
	{
	    int data; 
	    struct node *next;
	};
	
	struct node *head = NULL; //ilk d���m� temsil etsin
	struct node *last = NULL; //son d���m� temsil etsin

/***************** Liste Olu�turma K�sm� *********************/	//buketecrinozturk
	struct node* listeOlustur(int data)
	{
	    //printf("\n olusturulan liste [%d]\n",data);
	    struct node *temp = (struct node*)malloc(sizeof(struct node)); // bellekten yer tahsis ettik
	    if(NULL == temp)
	    {
	  		printf("\n Bellek dolu!!! Yer tahsis edemedik \n");
		    return NULL;
	    }
	    temp->data = data; // temp d���m�n data h�cresine data'y� at�yoruz.
	    temp->next = NULL; // temp d���m ilk ve tek d���m oldu�u i�in next h�cresine NULL at�yoruz.
	
	    head = last = temp; // ge�ici d���m ilk ve tek d���m oldu�u i�in ayn� zamanda son d���mde olmu� oluyor
	    return temp;
	}
	/***************** Listeye Eleman Ekleme K�sm� *********************/ //buketecrinozturk	
	struct node* elemanEkleme(int data, int liste_konum)
	{
	    if(NULL == head) //liste bo�sa
	    {
	        return (listeOlustur(data)); //liste olu�turuyoruz
	    }
		
	    struct node *temp = (struct node*)malloc(sizeof(struct node));
	    if(NULL == temp)
	    {
	        printf("\n Bellek dolu!!! Yer tahsis edemedik \n");
	        return NULL;
	    }
	    temp->data = data; //gelen veriyi temp d���m�n�n data h�cresine ekledik 
	    temp->next = NULL; // tempden sonra gelen d���m belli olmad��� i�in next h�cresini NULL yapt�k 
	
	    if(liste_konum==1) //listenin sonuna eleman eklenecek ise
	    {
	        last->next = temp; // son d���m�n next h�cresi temp d���m� g�stersin
	        last = temp; //son d���m art�k temp d���m oldu 
	    }
	    else if(liste_konum==0)//listenin ba��na eleman eklenecek ise
	    {
	        temp->next = head;// temp d���m�n next h�cresi art�k head  d���m� g�stersin
	        head = temp; //ilk d���m art�k temp d���m oldu 
	    }
	    return temp;
	}
	
	/***************** Listede Eleman Arama K�sm� *********************/ //buketecrinozturk	

	struct node* elemanArama(int data, struct node **prev)
	{
	    struct node *list = head;
	    struct node *tmp = NULL;
	    bool found = false;
	
	    printf("\n Aranacak eleman [%d] \n",data);
	
	    while(list != NULL) // son elemana gelene kadar d�ng� �al��s�n
	    {
	        if(list->data == data)
	        {
	            found = true;
	            break;
	        }
	        else
	        {
	            tmp = list;
	            list = list->next;
	        }
	    }
	
	    if(true == found)
	    {
	      
	        if(prev) // bu k�sm� silme i�lemi i�in kullan�yoruz
	            *prev = tmp;
	        return list;
	    }
	    else
	    {
	        return NULL;
	    }
	}
	
	/***************** Listeden Eleman Silme K�sm� *********************/ //buketecrinozturk	

	int silinecekEleman(int data)
	{
	    struct node *prev = NULL;
	    struct node *del = NULL;
	
	    printf("\n ***silinecek eleman [%d] \n",data);
	
	    del = elemanArama(data,&prev);
	    if(del == NULL) 
	    {
	        return -1; // silinecek eleman bulunamad� ise
	    }
	    else
	    {
	        if(prev != NULL){ // silinecek eleman arada bir yerde ise
	            prev->next = del->next; // silinecek d���m�n sonras�ndaki d���m 
										//silinecek d���m�n �ncesindeki d���me ba�land�
	            printf("\n adim1***del->data [%d] \n",del->data);
			}
	        if(del == last) // silinecek eleman sonda ise
	        {
	            last = prev; // son d���m art�k prev d���m� oldu
	            printf("\n adim2***last->data [%d] \n",last->data);
	            last->next=NULL;

	        }
	        else if(del == head) // silinecek eleman ba�ta ise
	        {
	            head = del->next; // head d���m�ne art�k bir sonraki d���m oldu.
	            printf("\n adim3***head->next [%d] \n",head->next);

	        }
	    }
	
	    free(del);
	    del = NULL;
	
	    return 0;
	} 
	
	/***************** Listeyi Silmek *********************/ //buketecrinozturk
	void listeyiSil()
	{
		struct node *list = head;
		struct node *gecici=NULL;
		while(head!=NULL){
			gecici=head;
			head=head->next;
			free(gecici);
		}
		
	}
	
	/***************** Listedeki Verileri Listeleme K�sm� *********************/ //buketecrinozturk	

	void print_list(void)
	{
	    struct node *list = head;
	
	    printf("\n -------Listeleme Basliyor------- \n");
	    while(list != NULL)
	    {
	        printf("\n [%d] \n",list->data);
	        list = list->next;
	    }
	    printf("\n -------Listeleme Bitti------- \n");
	
	    return;
	}
	
	/***************** Main K�sm� *********************/	

	int main(void)
{
    int i = 0, delval = 0;
    struct node *list = NULL;

    //print_list();

    for(i = 5; i<10; i++)
        elemanEkleme(i,1); //listenin sonuna eleman ekleme

    //print_list();

    for(i = 4; i>0; i--)
        elemanEkleme(i,0);//listenin ba��na eleman ekleme

   // print_list();// listele

    for(i = 1; i<10; i += 4)
    {
    	int deger=7;
        list = elemanArama(deger, NULL);
        if(NULL == list)
        {
        //    printf("\n Aranan deger [val = %d] bulunamadi\n",i);
        }
        else
        {
          //  printf("\n Arana deger [val = %d] bulundu\n",list->data);
        }

       // print_list();// listele

        delval = silinecekEleman(deger);
      
        print_list();// listele
        
    }
   		 listeyiSil();
  
    return 0;
}
