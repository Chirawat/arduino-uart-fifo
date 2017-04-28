#define MAXQ 3
typedef struct{
  uint8_t item[MAXQ];
  int8_t front, rear;
}QType;
QType que1;

void fifo_flush(QType *que){
    que->front = -1;
    que->rear = -1;
}

bool fifo_isEmpty(QType *que){
    if(que->front == -1){
        return true;
    }
    else{
        return false;
    }
}

bool fifo_isFull(QType *que){
    int nextrear;
    if(que->rear == MAXQ - 1){
        nextrear = 0;
    }
    else{
        nextrear = que->rear+1;
    }
    if(nextrear == que->front)
      return true;
    else
      return false;
}

void fifo_write(QType *que, uint8_t item){
    if(que->rear == MAXQ - 1){
        que->rear = 0;
    }
    else{
        que->rear++;
    }
    que->item[que->rear] = item;
    if(que->front == -1){
        que->front = 0;
    }
}

void fifo_read(QType *que, uint8_t *item){
    *item = que->item[que->front];
    if(que->front == que->rear)
        fifo_flush(que);
    else
        if(que->front == MAXQ - 1)
            que->front = 0;
        else    
            que->front++;
}

void fifo_status(QType *que){
  uint8_t ret;
  fifo_isFull(que) ? Serial.print("FIFO full") : Serial.print("FIFO not full");
  fifo_isEmpty(que) ? Serial.println(" ,FIFO empty") : Serial.println(" ,FIFO not empty");
  
  Serial.print("Front = ");
  Serial.println(que->front);
  Serial.print("Rear = ");
  Serial.println(que->rear);
  Serial.print("que[front] = ");
  Serial.println(que->item[que->front]);
  
  Serial.println();
}

void setup() {
  uint8_t ret;
  Serial.begin(115200);
  Serial.println("Started...");  

  Serial.println("FIFO initialised.");
  fifo_status(&que1);

  fifo_flush(&que1);
  Serial.println("FIFO Flushed.");
  fifo_status(&que1);

  Serial.println("FIFO has been written.");
  fifo_write(&que1, 0x01);
  fifo_status(&que1);
  
  Serial.println("FIFO has been written."); 
  fifo_write(&que1, 0x02);
  fifo_status(&que1);

  Serial.println("FIFO has been written.");
  fifo_write(&que1, 0x03);
  fifo_status(&que1);

  Serial.println("FIFO has been read.");
  fifo_read(&que1, &ret);
  fifo_status(&que1);
  
  Serial.println("FIFO has been read.");
  fifo_read(&que1, &ret);
  fifo_status(&que1);

  Serial.println("FIFO has been read.");
  fifo_read(&que1, &ret);
  fifo_status(&que1);

  Serial.println("FIFO has been read.");
  fifo_read(&que1, &ret);
  fifo_status(&que1);
}
void loop() {
  
}
