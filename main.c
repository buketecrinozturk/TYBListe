#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <stdbool.h>


/*****************struct oluþturuyoruz *********************/ //buketecrinozturk
	struct node
	{
	    int data; 
	    struct node *next;
	};
	
	struct node *head = NULL; //ilk düðümü temsil etsin
	struct node *last = NULL; //son düðümü temsil etsin

/***************** Liste Oluþturma Kýsmý *********************/	//buketecrinozturk
	struct node* listeOlustur(int data)
	{
	    //printf("\n olusturulan liste [%d]\n",data);
	    struct node *temp = (struct node*)malloc(sizeof(struct node)); // bellekten yer tahsis ettik
	    if(NULL == temp)
	    {
	  		printf("\n Bellek dolu!!! Yer tahsis edemedik \n");
		    return NULL;
	    }
	    temp->data = data; // temp düðümün data hücresine data'yý atýyoruz.
	    temp->next = NULL; // temp düðüm ilk ve tek düðüm olduðu için next hücresine NULL atýyoruz.
	
	    head = last = temp; // geçici düðüm ilk ve tek düðüm olduðu için ayný zamanda son düðümde olmuþ oluyor
	    return temp;
	}
	/***************** Listeye Eleman Ekleme Kýsmý *********************/ //buketecrinozturk	
	struct node* elemanEkleme(int data, int liste_konum)
	{
	    if(NULL == head) //liste boþsa
	    {
	        return (listeOlustur(data)); //liste oluþturuyoruz
	    }
		
	    struct node *temp = (struct node*)malloc(sizeof(struct node));
	    if(NULL == temp)
	    {
	        printf("\n Bellek dolu!!! Yer tahsis edemedik \n");
	        return NULL;
	    }
	    temp->data = data; //gelen veriyi temp düðümünün data hücresine ekledik 
	    temp->next = NULL; // tempden sonra gelen düðüm belli olmadýðý için next hücresini NULL yaptýk 
	
	    if(liste_konum==1) //listenin sonuna eleman eklenecek ise
	    {
	        last->next = temp; // son düðümün next hücresi temp düðümü göstersin
	        last = temp; //son düðüm artýk temp düðüm oldu 
	    }
	    else if(liste_konum==0)//listenin baþýna eleman eklenecek ise
	    {
	        temp->next = head;// temp düðümün next hücresi artýk head  düðümü göstersin
	        head = temp; //ilk düðüm artýk temp düðüm oldu 
	    }
	    return temp;
	}
	
	/***************** Listede Eleman Arama Kýsmý *********************/ //buketecrinozturk	

	struct node* elemanArama(int data, struct node **prev)
	{
	    struct node *list = head;
	    struct node *tmp = NULL;
	    bool found = false;
	
	    printf("\n Aranacak eleman [%d] \n",data);
	
	    while(list != NULL) // son elemana gelene kadar döngü çalýþsýn
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
	      
	        if(prev) // bu kýsmý silme iþlemi için kullanýyoruz
	            *prev = tmp;
	        return list;
	    }
	    else
	    {
	        return NULL;
	    }
	}
	
	/***************** Listeden Eleman Silme Kýsmý *********************/ //buketecrinozturk	

	int silinecekEleman(int data)
	{
	    struct node *prev = NULL;
	    struct node *del = NULL;
	
	    printf("\n ***silinecek eleman [%d] \n",data);
	
	    del = elemanArama(data,&prev);
	    if(del == NULL) 
	    {
	        return -1; // silinecek eleman bulunamadý ise
	    }
	    else
	    {
	        if(prev != NULL){ // silinecek eleman arada bir yerde ise
	            prev->next = del->next; // silinecek düðümün sonrasýndaki düðüm 
										//silinecek düðümün öncesindeki düðüme baðlandý
	            printf("\n adim1***del->data [%d] \n",del->data);
			}
	        if(del == last) // silinecek eleman sonda ise
	        {
	            last = prev; // son düðüm artýk prev düðümü oldu
	            printf("\n adim2***last->data [%d] \n",last->data);
	            last->next=NULL;

	        }
	        else if(del == head) // silinecek eleman baþta ise
	        {
	            head = del->next; // head düðümüne artýk bir sonraki düðüm oldu.
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
	
	/***************** Listedeki Verileri Listeleme Kýsmý *********************/ //buketecrinozturk	

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
	
	/***************** Main Kýsmý *********************/	

	int main(void)
{
    int i = 0, delval = 0;
    struct node *list = NULL;

    //print_list();

    for(i = 5; i<10; i++)
        elemanEkleme(i,1); //listenin sonuna eleman ekleme

    //print_list();

    for(i = 4; i>0; i--)
        elemanEkleme(i,0);//listenin baþýna eleman ekleme

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
