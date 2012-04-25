%module TextDetection

%include "boost_shared_ptr.i"

%include "stdint.i"
%include "std_list.i"
%include "std_vector.i"
%include "std_string.i"

%{
#define SWIG_FILE_WITH_INIT
#include "TextDetection/TextAreaFinder.h"

#ifndef SWIG_FILE_WITH_INIT
#  define NO_IMPORT_ARRAY
#endif
#include "stdio.h"
#include <numpy/arrayobject.h>
%}

%init %{
    import_array();
%}

%typemap(out) Eigen::Vector2f {
    $result = PyTuple_New( 2 );
    PyTuple_SetItem( $result, 0, PyFloat_FromDouble( $1.x() ) );
    PyTuple_SetItem( $result, 1, PyFloat_FromDouble( $1.y() ) );
}

%typemap(out) Eigen::Vector3f {
    $result = PyTuple_New( 3 );
    PyTuple_SetItem( $result, 0, PyFloat_FromDouble( $1.x() ) );
    PyTuple_SetItem( $result, 1, PyFloat_FromDouble( $1.y() ) );
    PyTuple_SetItem( $result, 2, PyFloat_FromDouble( $1.z() ) );
}

%typemap(out) Eigen::MatrixXi* 
{
    int dims[] =
    {
        $1->cols(),
        $1->rows()
    };
    
    $result = PyArray_SimpleNew( 2, dims, PyArray_INT );

    int numBytes = $1->rows()*$1->cols()*sizeof( int );
    void *pDst = PyArray_DATA((PyArrayObject*)$result);
    memcpy( pDst, $1->data(), numBytes );

    delete $1;

    $result = PyArray_Transpose( (PyArrayObject*)$result, NULL );
}

%typemap(out) Eigen::MatrixXf* 
{
    int dims[] =
    {
        $1->cols(),
        $1->rows()
    };
    
    $result = PyArray_SimpleNew( 2, dims, PyArray_FLOAT );

    int numBytes = $1->rows()*$1->cols()*sizeof( float );
    void *pDst = PyArray_DATA((PyArrayObject*)$result);
    memcpy( pDst, $1->data(), numBytes );

    delete $1;

    $result = PyArray_Transpose( (PyArrayObject*)$result, NULL );
}

%typemap(out) Eigen::MatrixXd* 
{
    int dims[] =
    {
        $1->cols(),
        $1->rows()
    };
    
    $result = PyArray_SimpleNew( 2, dims, PyArray_DOUBLE );

    int numBytes = $1->rows()*$1->cols()*sizeof( double );
    void *pDst = PyArray_DATA((PyArrayObject*)$result);
    memcpy( pDst, $1->data(), numBytes );

    delete $1;

    $result = PyArray_Transpose( (PyArrayObject*)$result, NULL );
}

%typemap(in) Eigen::Matrix4f 
{
    PyArrayObject* pMtx = (PyArrayObject*)$input;

    /* Check that it's the correct type */
    if ( NPY_FLOAT != PyArray_TYPE( pMtx ) 
        || 2 != pMtx->nd
        || PyArray_DIM( pMtx, 0 ) != 4
        || PyArray_DIM( pMtx, 1 ) != 4 )  
    {
        PyErr_SetString( PyExc_ValueError,
            "Matrix must be of type float32 and (4 x 4)." );
        return NULL;
    }

    void *pSrc = PyArray_DATA((PyArrayObject*)pMtx);
    memcpy( $1.data(), pSrc, 4*4*sizeof(float) );
    
    if ( pMtx->flags & NPY_C_CONTIGUOUS )
    {
        $1.transposeInPlace();
    }
}

%typemap(out) Eigen::Matrix4f 
{
    int dims[] =
    {
        $1.cols(),
        $1.rows()
    };
    
    $result = PyArray_SimpleNew( 2, dims, PyArray_FLOAT );

    int numBytes = $1.rows()*$1.cols()*sizeof( float );
    void *pDst = PyArray_DATA((PyArrayObject*)$result);
    memcpy( pDst, $1.data(), numBytes );

    $result = PyArray_Transpose( (PyArrayObject*)$result, NULL );
}

%newobject TextAreaFinder::TextAreaFinder;

%include "TextDetection/TextAreaFinder.h"



