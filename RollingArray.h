#ifndef RollingArray_h
#define RollingArray_h

class RollingArray {
  public:
    RollingArray(int alloc_size);
    void setLength(int size);

    int start_idx;
    float sum;
    float *values;
    
    float get(int index);
    void append(float value);

  private:
    int alloc_size;
    int size;
};

#endif