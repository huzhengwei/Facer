/*//////////////////////////////////////////////////////
//
// Copyright (c) 2011 huzhengwei. All rights reserved.
//
// Author:
//			huzhengwei, zhengwei_hu@163.com
//
///////////////////////////////////////////////////////*/
�����̣�MTCNN�����������Vgg-Face����
��Ŀ¼��
	DataBase: ���ݿ�(ʹ��LevelDBʵ�֣���������(��id)��vgg������ͼƬ·��)��
	image:ע��ͼƬ���棻
	vgg_face_caffe: Vgg-Faceģ�Ͳ�����
	model: MTCNNģ�Ͳ�����
	Facer: Facer����Ŀ����Ŀ¼��
	vggfeature��������⡢����ʶ�����ݿ��װ����Ŀ¼��
	Test: MTCNN���ܲ��ԣ���Դ��
	x64_release-��ִ���ļ���ڣ���ִ���ļ����
ʹ�ü�飺
1.����x64_release-��ִ���ļ���ڣ�ִ��Facer.exe���������棻
2.�����Զ�����ģ�Ͳ�������״̬����������ʾ����ʱ����Դ򿪲˵���->������ͷ��
3.�����Ĭ�Ͻ���ע����棨ʵʱ�������ע�ᰴť����ע�᣻
4.���ʶ���ǩ����10s��ʱ����ȴ������ֻ���֮�󼴿�ʶ��ѭ��ʶ�𡢸�����ʾ����
�����������������ʶ��Ϊͬ��idʱ���У�һ��ʶ����ʱ5s�����Ը�����Ҫ��ʱ10s��ʾ��

class�������������ռ�Facer�У�
	abstract class�����������ʵ�֣�
		DB�����ݿ�������
		Detector������������������
		Feature��������ȡ�������
		Facer��ע����ʶ��������Ҳ��ʵ���ࣻ
	����ʵ�֣�
		LevelDB��LevelDBʵ�����ݿ⣻
		MtcnnDetector��MTCNN��������㷨��
		VggFeature:Vgg-Face������
	�����ࣺ
		FaceRec�������߳���ռ䣻