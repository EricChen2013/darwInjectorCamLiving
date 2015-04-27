#ifndef _CamH264VideoStreamFramer_HH
#define _CamH264VideoStreamFramer_HH

#include <H264VideoStreamFramer.hh>
#include "GroupsockHelper.hh"

#define FRAME_PER_SEC 20
#define stream_buf_size 200
extern int stream_buf_ptr_tail;
extern unsigned char *stream_buf[stream_buf_size];
extern int stream_buf_len[stream_buf_size];



class CamH264VideoStreamFramer: public H264VideoStreamFramer
{
public:
	virtual ~CamH264VideoStreamFramer();
	CamH264VideoStreamFramer(UsageEnvironment& env, 
		FramedSource* inputSource);

	static CamH264VideoStreamFramer* createNew(UsageEnvironment& env, FramedSource* inputSource);
	//virtual Boolean currentNALUnitEndsAccessUnit();
	virtual void doGetNextFrame();

private:
	char tmpbuf[300000];
	unsigned int tailptr;
	int currentptr;
	

//	static ICameraCaptuer* m_pCamera;
//	H264EncWrapper* m_pH264Enc;
//	H264DecWrapper* m_pH264Dec;
//
//	TNAL* m_pNalArray;
//	int m_iCurNalNum;	//当前Frame一共有多少个NAL
//	int m_iCurNal;	//当前使用的是第几个NAL
//	unsigned int m_iCurFrame;
};


#endif