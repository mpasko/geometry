class EmptyNodeException : public General_exception {
public:
    EmptyNodeException() : General_exception(){
    }

    EmptyNodeException(std::string cause) : General_exception(cause){
    }
private:

};