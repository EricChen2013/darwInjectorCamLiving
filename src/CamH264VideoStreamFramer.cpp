#include <CamH264VideoStreamFramer.h>

CamH264VideoStreamFramer::CamH264VideoStreamFramer(UsageEnvironment& env,FramedSource* inputSource):
H264VideoStreamFramer(env, inputSource, False, False)
{
	currentptr=stream_buf_ptr_tail;
	tailptr=0;
}

CamH264VideoStreamFramer::~CamH264VideoStreamFramer()
{}

CamH264VideoStreamFramer* CamH264VideoStreamFramer::createNew(
	UsageEnvironment& env,
	FramedSource* inputSource)
{
	CamH264VideoStreamFramer* fr;
	fr = new CamH264VideoStreamFramer(env, inputSource);
	return fr;
}


void CamH264VideoStreamFramer::doGetNextFrame()
{
	gettimeofday(&fPresentationTime, NULL);
	while(currentptr==stream_buf_ptr_tail) usleep(1000);
	//printf("Video!\n");

	while(currentptr!=stream_buf_ptr_tail)
	{
		if(stream_buf_len[currentptr]+tailptr>300000) stream_buf_len[currentptr]=300000-tailptr;
		memcpy(tmpbuf+tailptr,(char *)stream_buf[currentptr],stream_buf_len[currentptr]);
		tailptr+=stream_buf_len[currentptr];
		currentptr=(currentptr+1)%stream_buf_size;	
	}


	if(tailptr>fMaxSize)
	{
		tailptr-=fMaxSize;
		fFrameSize=fMaxSize;
		memcpy(fTo,tmpbuf,fMaxSize);
		memcpy(tmpbuf,tmpbuf+fMaxSize,tailptr);
	}
	else
	{
		fFrameSize=tailptr;
		memcpy(fTo,tmpbuf,tailptr);
		tailptr=0;
	}

	fDurationInMicroseconds = 30000;
	afterGetting(this);  

}
