#version 330 core
layout (location = 0) in vec3 position; // position����������λ��ֵΪ0

out vec4 vertexColor; // ΪƬ����ɫ��ָ��һ����ɫ���

void main()
{
    gl_Position = vec4(position, 1.0); // ע��������ΰ�һ��vec3��Ϊvec4�Ĺ������Ĳ���
    vertexColor = vec4(0.5f, 0.0f, 0.0f, 1.0f); // �������������Ϊ����ɫ
}