

#pragma once

#include <CubismFramework.hpp>
#include <Model/CubismUserModel.hpp>
#include <ICubismModelSetting.hpp>
#include <Type/csmRectF.hpp>
#include <Rendering/OpenGL/CubismOffscreenSurface_OpenGLES2.hpp>





/**
 * @brief �û�ʵ��ʹ�õ�ģ�͵�ʵ����<br>
 *         ����ģ�����ɣ�����������ɣ����´������Ⱦ��
 *
 */

class LAppTextureManager;


class myUserModel : public Csm::CubismUserModel
{
public:
    /**
     * @brief ���󥹥ȥ饯��   ���캯��
     */
    myUserModel();

    /**
     * @brief �ǥ��ȥ饯��   ��������
     *
     */
    virtual ~myUserModel();

    /**
     * @brief model3.json���ä��줿�ǥ��쥯�ȥ�ȥե�����ѥ������ǥ�����ɤ���  ��model3.json���ڵ�Ŀ¼���ļ�·������ģ��
     *
     */
    void LoadAssets(const Csm::csmChar* dir, const  Csm::csmChar* fileName);

    /**
     * @brief ��������٘��B����     ������Ⱦ��
     *
     */
    void ReloadRenderer();

    /**
     * @brief   ��ǥ�θ��I����ǥ�Υѥ��`�������軭״�B��Q�����롣   ģ�͸��´��� ͼֽ״̬��ģ�Ͳ���ȷ����
     *
     */
    void Update();

    /**
     * @brief   ��ǥ���軭����I����ǥ���軭������g��View-Projection���Ф�ɤ���   ����ģ�͵Ĺ��̡� ͨ������ģ�͵Ŀռ��View-Projection����
     *
     * @param[in]  matrix  View-Projection����
     */
    void Draw(Csm::CubismMatrix44& matrix);

    /**
     * @brief   ������ָ��������`�������������_ʼ���롣   ��ʼ���Ų���ָ���Ķ���
     *
     * @param[in]   group                       ��`����󥰥�`����   motion group����
     * @param[in]   no                          ����`���ڤη���   group�����
     * @param[in]   priority                    ���ȶ�
     * @param[in]   onFinishedMotionHandler     ��`����������K�˕r�˺��ӳ�����륳�`��Хå��v����NULL�Έ��ϡ����ӳ�����ʤ���   ��̬���Ž���ʱ���õĻص������� ���ΪNULL���򲻵��á�
     * @return                                  �_ʼ������`�������R�e���Ť򷵤������e�Υ�`����󤬽K�ˤ������񤫤��ж�����IsFinished()��������ʹ�ä��롣�_ʼ�Ǥ��ʤ��r�ϡ�-1��

     ���ؿ�ʼ�˶��ı�ʶ�š� ��IsFinished�����Ĳ�����ʹ�ã���ȷ�������˶��Ƿ��ѽ����� �޷�����ʱΪ�� -1��

     */
    Csm::CubismMotionQueueEntryHandle StartMotion(const Csm::csmChar* group, Csm::csmInt32 no, Csm::csmInt32 priority, Csm::ACubismMotion::FinishedMotionCallback onFinishedMotionHandler = NULL);

    /**
     * @brief   ��ʼ�������ѡ��Ķ���
     *
     * @param[in]   group                       ��`����󥰥�`����   motion group����
     * @param[in]   priority                    ���ȶ�
     * @param[in]   onFinishedMotionHandler     ��`����������K�˕r�˺��ӳ�����륳�`��Хå��v����NULL�Έ��ϡ����ӳ�����ʤ���  ��̬���Ž���ʱ���õĻص������� ���ΪNULL���򲻵��á�
     * @return                                  �_ʼ������`�������R�e���Ť򷵤������e�Υ�`����󤬽K�ˤ������񤫤��ж�����IsFinished()��������ʹ�ä��롣�_ʼ�Ǥ��ʤ��r�ϡ�-1��

      ���ؿ�ʼ�˶��ı�ʶ�š� ��IsFinished�����Ĳ�����ʹ�ã���ȷ�������˶��Ƿ��ѽ����� �޷�����ʱΪ�� -1��
     */
    Csm::CubismMotionQueueEntryHandle StartRandomMotion(const Csm::csmChar* group, Csm::csmInt32 priority, Csm::ACubismMotion::FinishedMotionCallback onFinishedMotionHandler = NULL);

    /**
     * @brief   ������ָ�����������`�����򥻥åȤ���  ���ò���ָ���ı��ʽ�˶�
     *
     * @param   expressionID    �����`������ID
     */
    void SetExpression(const Csm::csmChar* expressionID);

    /**
     * @brief   ��������x�Ф줿�����`�����򥻥åȤ���   �������ѡ����沿���鶯��
     *
     */
    void SetRandomExpression();

    /**
    * @brief   ���٥�Ȥΰk����ܤ�ȡ��  �����¼�����
    *
    */
    virtual void MotionEventFired(const Live2D::Cubism::Framework::csmString& eventValue);

    /**
     * @brief    �������ж��ƥ��ȡ�<br>  ���м��
     *            ָ��ID��픵�ꥹ�Ȥ�����Τ�Ӌ�㤷�����ˤ����ι����ڤ��ж����롣  ��ָ��ID�Ķ����б��м����һ�����Σ�Ȼ��ȷ�������Ƿ��ھ��η�Χ�ڡ�
     *
     * @param[in]   hitAreaName     �������ж���ƥ��Ȥ��댝���ID   ���������ж���ID
     * @param[in]   x               �ж����Ф�X����     X�����ж�
     * @param[in]   y               �ж����Ф�Y����     Y�����ж�
     */
    virtual Csm::csmBool HitTest(const Csm::csmChar* hitAreaName, Csm::csmFloat32 x, Csm::csmFloat32 y);


    virtual Csm::ICubismModelSetting* GetModelSetting();
        














    /**
     * @brief   �e���`���åȤ��軭�����H��ʹ�ä���Хåե���ȡ��     ���Ƶ���һ��Ŀ��ʱ��ȡ������
     */
    Csm::Rendering::CubismOffscreenFrame_OpenGLES2& GetRenderBuffer();

protected:
    /**
     *  @brief  ��ǥ���軭����I����ǥ���軭������g��View-Projection���Ф�ɤ���
     *����ģ�͵Ĺ��̡� ͨ������ģ�͵Ŀռ��View-Projection����

     */
    void DoDraw();

private:
    /**
     * @brief model3.json�����ǥ�����ɤ��롣<br>  ��model3.json����ģ��
     *         model3.json��ӛ���ˏ��äƥ�ǥ����ɡ���`�������������ʤɤΥ���ݩ`�ͥ�����ɤ��Ф���
     *      ����model3.json�������������������ģ�����ɣ��˶������������
     * @param[in]   setting     ICubismModelSetting�Υ��󥹥���
     *
     */
    void SetupModel(Csm::ICubismModelSetting* setting);

    /**
     * @brief OpenGL�Υƥ��������˥åȤ˥ƥ���������`�ɤ���   ��������ص�OpenGL����Ԫ��
     *
     */
    void SetupTextures();

    /**
     * @brief   ��`�����ǩ`���򥰥�`��������һ���ǥ�`�ɤ��롣<br>   �����������������˶����ݡ�
     *           ��`�����ǩ`������ǰ���ڲ���ModelSetting����ȡ�ä��롣  �˶����ݵ������Ǵ�ModelSetting�ڲ���õ�
     *
     * @param[in]   group  ��`�����ǩ`���Υ���`����    motion���ݵ�group��
     */
    void PreloadMotionGroup(const Csm::csmChar* group);

    /**
     * @brief   ��`�����ǩ`���򥰥�`��������һ���ǽ�Ť��롣<br>  ������group�����ͷ�motion���ݡ�
     *           ��`�����ǩ`������ǰ���ڲ���ModelSetting����ȡ�ä��롣    motion���ݵ������Ǵ�ModelSetting�ڲ���õ�
     *
     * @param[in]   group  ��`�����ǩ`���Υ���`����   motion���ݵ�group��
     */
    void ReleaseMotionGroup(const Csm::csmChar* group) const;

    /**
    * @brief ���٤ƤΥ�`�����ǩ`���ν��   �ͷ������˶�����
    *
    * ���٤ƤΥ�`�����ǩ`�����Ť��롣    �ͷ�����motion����
    */
    void ReleaseMotions();

    /**
    * @brief ���٤Ƥα���ǩ`���ν��   �ͷ������沿��������
    *
    * ���٤Ƥα���ǩ`�����Ť��롣   �ͷ������沿��������
    */
    void ReleaseExpressions();

    Csm::ICubismModelSetting* _modelSetting; ///< ��ǥ륻�åƥ������   Model Setting ����Ϣ
    Csm::csmString _modelHomeDir; ///< ��ǥ륻�åƥ��󥰤��ä��줿�ǥ��쥯�ȥ�  ģ���������ڵ�Ŀ¼
    Csm::csmFloat32 _userTimeSeconds; ///< �ǥ륿�r�g�ηe�ゎ[��]    ����ʱ��Ļ���ֵ[��]
    Csm::csmVector<Csm::CubismIdHandle> _eyeBlinkIds; ///< ��ǥ���O�����줿�ޤФ����C���åѥ��`��ID     ��ģ�������õ�գ�۹��ܲ���ID
    Csm::csmVector<Csm::CubismIdHandle> _lipSyncIds; ///< ��ǥ���O�����줿��åץ��󥯙C���åѥ��`��ID   ģ�������õĿ���ͬ�����ܵĲ���ID
    Csm::csmMap<Csm::csmString, Csm::ACubismMotion*>   _motions; ///< �i���z�ޤ�Ƥ����`�����Υꥹ��    ����motion�б�
    Csm::csmMap<Csm::csmString, Csm::ACubismMotion*>   _expressions; ///< �i���z�ޤ�Ƥ������Υꥹ��      ���ر�������
    Csm::csmVector<Csm::csmRectF> _hitArea;
    Csm::csmVector<Csm::csmRectF> _userArea;
    const Csm::CubismId* _idParamAngleX; ///< �ѥ��`��ID: ParamAngleX      ����id
    const Csm::CubismId* _idParamAngleY; ///< �ѥ��`��ID: ParamAngleX
    const Csm::CubismId* _idParamAngleZ; ///< �ѥ��`��ID: ParamAngleX
    const Csm::CubismId* _idParamBodyAngleX; ///< �ѥ��`��ID: ParamBodyAngleX
    const Csm::CubismId* _idParamEyeBallX; ///< �ѥ��`��ID: ParamEyeBallX
    const Csm::CubismId* _idParamEyeBallY; ///< �ѥ��`��ID: ParamEyeBallXY







    LAppTextureManager* _textureManager;
    Csm::Rendering::CubismOffscreenFrame_OpenGLES2  _renderBuffer;   ///< �ե�`��Хåե�������軭��        ֡���壿����
};



