template<typename T>
class Stack{
  class Block{
    Block* next;
    T data;
    public:
    explicit Block(const T& data) : next(nullptr), data(data){}
    ~Block() = default;
    Block* GetNext() const; 
    void SetNext(Block* next);
    T& GetData();
  };
  Block* head;
  Block* tail;
  int size;
  public:
  Stack() : head(nullptr), tail(nullptr), size(0){}
  Stack(const Stack& other) = delete;
  ~Stack();
  void Push(const T& data);
  T Pop();
  T& Peek();
  bool IsEmpty() const;
  
  //Puts top on top on bot and empties top
  static void Merge(Stack& Bot, Stack& Top);
};

//Block funcs

template<typename T>
typename Stack<T>::Block* Stack<T>::Block::GetNext() const{
  return this->next;
}

template<typename T>
void Stack<T>::Block::SetNext(Block* next){
  this->next = next;
}

template<typename T>
T& Stack<T>::Block::GetData (){
  return this->data;
}

//Stack funcs


template<typename T>
Stack<T>::~Stack(){
  while (this->head != nullptr){
    Block* curr = head;
    head = head->GetNext();
    delete curr;
  }
}

template<typename T>
void Stack<T>::Push(const T& data){
  Block* head = new Block(data);
  head->SetNext(this->head);
  if(this->head == nullptr) this->tail = head;
  this->head = head;
  this->size++;
}

template<typename T>
T Stack<T>::Pop(){
  T data = this->head->GetData();
  Block* temp = this->head;
  this->head = this->head->GetNext();
  if(this->head == nullptr) this->tail = nullptr;
  delete temp;
  this->size--;
  return data;
}

template<typename T>
bool Stack<T>::IsEmpty() const{
  return this->head == nullptr;
}

template<typename T>
void Stack<T>::Merge(Stack<T>& Bot, Stack<T>& Top){
  if (Bot.head == nullptr) {
      Bot.head = Top.head;
      Bot.tail = Top.tail;
      Top.head = nullptr;
      Top.tail = nullptr;
      return;
  }
  if (Top.head == nullptr) return;
    Top.tail->SetNext(Bot.head); 
    Bot.head = Top.head;
    Top.head = nullptr;
    Top.tail = nullptr;
}

template<typename T>
T& Stack<T>::Peek(){
  return this->head->GetData();
}
