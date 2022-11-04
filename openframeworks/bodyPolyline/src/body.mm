#include "body.h"

@implementation Body

-(NSArray*)detect:(CGImageRef)image{
  
    VNDetectHumanBodyPoseRequest *req = [[VNDetectHumanBodyPoseRequest new] autorelease];
    NSDictionary *d = [[[NSDictionary alloc] init] autorelease];
    VNImageRequestHandler *handler = [[[VNImageRequestHandler alloc] initWithCGImage:image options:d] autorelease];

    [handler performRequests:@[req] error:nil];

    return req.results;
}
@end

BODY::BODY(){
  tracker = [[Body alloc] init];
}

void BODY::detect(ofPixels pix) {
    CGImageRef image = CGImageRefFromOfPixels(pix,(int)pix.getWidth(),(int)pix.getHeight(),(int)pix.getNumChannels());
    NSArray* arr = [tracker detect:image];
    NSError *err;
    
    n_det = 0;

    /// see https://developer.apple.com/documentation/vision/detecting_human_body_poses_in_images for diagram of all possible body points
    
    for(VNHumanBodyPoseObservation *observation in arr){

        /// get all the points
        NSDictionary <VNHumanBodyPoseObservationJointName, VNRecognizedPoint *> *allPts = [observation recognizedPointsForJointsGroupName:VNHumanBodyPoseObservationJointsGroupNameAll error:&err];
    
        VNRecognizedPoint *RightEye         = [allPts objectForKey:VNHumanBodyPoseObservationJointNameRightEye];
        VNRecognizedPoint *LeftEye          = [allPts objectForKey:VNHumanBodyPoseObservationJointNameLeftEye];
        VNRecognizedPoint *RightEar         = [allPts objectForKey:VNHumanBodyPoseObservationJointNameRightEar];
        VNRecognizedPoint *Nose             = [allPts objectForKey:VNHumanBodyPoseObservationJointNameNose];
        VNRecognizedPoint *LeftEar          = [allPts objectForKey:VNHumanBodyPoseObservationJointNameLeftEar];
        VNRecognizedPoint *RightWrist       = [allPts objectForKey:VNHumanBodyPoseObservationJointNameRightWrist];
        VNRecognizedPoint *RightElbow       = [allPts objectForKey:VNHumanBodyPoseObservationJointNameRightElbow];
        VNRecognizedPoint *RightShoulder    = [allPts objectForKey:VNHumanBodyPoseObservationJointNameRightShoulder];
        VNRecognizedPoint *Neck             = [allPts objectForKey:VNHumanBodyPoseObservationJointNameNeck];
        VNRecognizedPoint *LeftShoulder     = [allPts objectForKey:VNHumanBodyPoseObservationJointNameLeftShoulder];
        VNRecognizedPoint *LeftElbow        = [allPts objectForKey:VNHumanBodyPoseObservationJointNameLeftElbow];
        VNRecognizedPoint *LeftWrist        = [allPts objectForKey:VNHumanBodyPoseObservationJointNameLeftWrist];
        VNRecognizedPoint *RightHip         = [allPts objectForKey:VNHumanBodyPoseObservationJointNameRightHip];
        VNRecognizedPoint *Root             = [allPts objectForKey:VNHumanBodyPoseObservationJointNameRoot];
        VNRecognizedPoint *LeftHip          = [allPts objectForKey:VNHumanBodyPoseObservationJointNameLeftHip];
        VNRecognizedPoint *RightKnee        = [allPts objectForKey:VNHumanBodyPoseObservationJointNameRightKnee];
        VNRecognizedPoint *LeftKnee         = [allPts objectForKey:VNHumanBodyPoseObservationJointNameLeftKnee];
        VNRecognizedPoint *RightAnkle       = [allPts objectForKey:VNHumanBodyPoseObservationJointNameRightAnkle];
        VNRecognizedPoint *LeftAnkle        = [allPts objectForKey:VNHumanBodyPoseObservationJointNameLeftAnkle];

        
        detections[n_det][BODY_RIGHTEYE     ].x = RightEye     .location.x * pix.getWidth();
        detections[n_det][BODY_LEFTEYE      ].x = LeftEye      .location.x * pix.getWidth();
        detections[n_det][BODY_RIGHTEAR     ].x = RightEar     .location.x * pix.getWidth();
        detections[n_det][BODY_NOSE         ].x = Nose         .location.x * pix.getWidth();
        detections[n_det][BODY_LEFTEAR      ].x = LeftEar      .location.x * pix.getWidth();
        detections[n_det][BODY_RIGHTWRIST   ].x = RightWrist   .location.x * pix.getWidth();
        detections[n_det][BODY_RIGHTELBOW   ].x = RightElbow   .location.x * pix.getWidth();
        detections[n_det][BODY_RIGHTSHOULDER].x = RightShoulder.location.x * pix.getWidth();
        detections[n_det][BODY_NECK         ].x = Neck         .location.x * pix.getWidth();
        detections[n_det][BODY_LEFTSHOULDER ].x = LeftShoulder .location.x * pix.getWidth();
        detections[n_det][BODY_LEFTELBOW    ].x = LeftElbow    .location.x * pix.getWidth();
        detections[n_det][BODY_LEFTWRIST    ].x = LeftWrist    .location.x * pix.getWidth();
        detections[n_det][BODY_RIGHTHIP     ].x = RightHip     .location.x * pix.getWidth();
        detections[n_det][BODY_ROOT         ].x = Root         .location.x * pix.getWidth();
        detections[n_det][BODY_LEFTHIP      ].x = LeftHip      .location.x * pix.getWidth();
        detections[n_det][BODY_RIGHTKNEE    ].x = RightKnee    .location.x * pix.getWidth();
        detections[n_det][BODY_LEFTKNEE     ].x = LeftKnee     .location.x * pix.getWidth();
        detections[n_det][BODY_RIGHTANKLE   ].x = RightAnkle   .location.x * pix.getWidth();
        detections[n_det][BODY_LEFTANKLE    ].x = LeftAnkle    .location.x * pix.getWidth();


        detections[n_det][BODY_RIGHTEYE     ].y = (1-RightEye     .location.y) * pix.getHeight();
        detections[n_det][BODY_LEFTEYE      ].y = (1-LeftEye      .location.y) * pix.getHeight();
        detections[n_det][BODY_RIGHTEAR     ].y = (1-RightEar     .location.y) * pix.getHeight();
        detections[n_det][BODY_NOSE         ].y = (1-Nose         .location.y) * pix.getHeight();
        detections[n_det][BODY_LEFTEAR      ].y = (1-LeftEar      .location.y) * pix.getHeight();
        detections[n_det][BODY_RIGHTWRIST   ].y = (1-RightWrist   .location.y) * pix.getHeight();
        detections[n_det][BODY_RIGHTELBOW   ].y = (1-RightElbow   .location.y) * pix.getHeight();
        detections[n_det][BODY_RIGHTSHOULDER].y = (1-RightShoulder.location.y) * pix.getHeight();
        detections[n_det][BODY_NECK         ].y = (1-Neck         .location.y) * pix.getHeight();
        detections[n_det][BODY_LEFTSHOULDER ].y = (1-LeftShoulder .location.y) * pix.getHeight();
        detections[n_det][BODY_LEFTELBOW    ].y = (1-LeftElbow    .location.y) * pix.getHeight();
        detections[n_det][BODY_LEFTWRIST    ].y = (1-LeftWrist    .location.y) * pix.getHeight();
        detections[n_det][BODY_RIGHTHIP     ].y = (1-RightHip     .location.y) * pix.getHeight();
        detections[n_det][BODY_ROOT         ].y = (1-Root   .location.y) * pix.getHeight();
        detections[n_det][BODY_LEFTHIP      ].y = (1-LeftHip      .location.y) * pix.getHeight();
        detections[n_det][BODY_RIGHTKNEE    ].y = (1-RightKnee    .location.y) * pix.getHeight();
        detections[n_det][BODY_LEFTKNEE     ].y = (1-LeftKnee     .location.y) * pix.getHeight();
        detections[n_det][BODY_RIGHTANKLE   ].y = (1-RightAnkle   .location.y) * pix.getHeight();
        detections[n_det][BODY_LEFTANKLE    ].y = (1-LeftAnkle    .location.y) * pix.getHeight();


        detections[n_det][BODY_RIGHTEYE     ].z = RightEye     .confidence;
        detections[n_det][BODY_LEFTEYE      ].z = LeftEye      .confidence;
        detections[n_det][BODY_RIGHTEAR     ].z = RightEar     .confidence;
        detections[n_det][BODY_NOSE         ].z = Nose         .confidence;
        detections[n_det][BODY_LEFTEAR      ].z = LeftEar      .confidence;
        detections[n_det][BODY_LEFTWRIST    ].z = LeftWrist    .confidence;
        detections[n_det][BODY_LEFTELBOW    ].z = LeftElbow    .confidence;
        detections[n_det][BODY_LEFTSHOULDER ].z = LeftShoulder .confidence;
        detections[n_det][BODY_NECK         ].z = Neck         .confidence;
        detections[n_det][BODY_RIGHTSHOULDER].z = RightShoulder.confidence;
        detections[n_det][BODY_RIGHTELBOW   ].z = RightElbow   .confidence;
        detections[n_det][BODY_RIGHTWRIST   ].z = RightWrist   .confidence;
        detections[n_det][BODY_LEFTHIP      ].z = LeftHip      .confidence;
        detections[n_det][BODY_ROOT         ].z = Root         .confidence;
        detections[n_det][BODY_RIGHTHIP     ].z = RightHip     .confidence;
        detections[n_det][BODY_RIGHTKNEE    ].z = RightKnee    .confidence;
        detections[n_det][BODY_LEFTKNEE     ].z = LeftKnee     .confidence;
        detections[n_det][BODY_RIGHTANKLE   ].z = RightAnkle   .confidence;
        detections[n_det][BODY_LEFTANKLE    ].z = LeftAnkle    .confidence;
        
        scores[n_det] = observation.confidence;
        n_det = (n_det + 1) % MAX_DET;
        
      }
    
      CGImageRelease(image);
    
}


CGImageRef BODY::CGImageRefFromOfPixels( ofPixels & img, int width, int height, int numberOfComponents ){
  
    int bitsPerColorComponent = 8;
    int rawImageDataLength = width * height * numberOfComponents;
    BOOL interpolateAndSmoothPixels = NO;
    CGBitmapInfo bitmapInfo = kCGBitmapByteOrderDefault;
    CGColorRenderingIntent renderingIntent = kCGRenderingIntentDefault;
    CGDataProviderRef dataProviderRef;
    CGColorSpaceRef colorSpaceRef;
    CGImageRef imageRef;
  
    GLubyte *rawImageDataBuffer =  (unsigned char*)(img.getData());
    dataProviderRef = CGDataProviderCreateWithData(NULL,  rawImageDataBuffer, rawImageDataLength, nil);
    if(numberOfComponents>1)
    {
        colorSpaceRef = CGColorSpaceCreateDeviceRGB();
    }
    else
    {
        colorSpaceRef = CGColorSpaceCreateDeviceGray();
    }
    imageRef = CGImageCreate(width, height, bitsPerColorComponent, bitsPerColorComponent * numberOfComponents, width * numberOfComponents, colorSpaceRef, bitmapInfo, dataProviderRef, NULL, interpolateAndSmoothPixels, renderingIntent);
  
    CGDataProviderRelease(dataProviderRef);
  
    return imageRef;
}
