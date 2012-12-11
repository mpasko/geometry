/** \brief Wyjąek rzucany gdy węzeł nie zawiera w środku punktu, mimo, że zakładaliśmy coś przciwnego.*/
class EmptyNodeException : public General_exception {
public:
    EmptyNodeException() : General_exception(){
    }

    EmptyNodeException(std::string cause) : General_exception(cause){
    }
private:

};
