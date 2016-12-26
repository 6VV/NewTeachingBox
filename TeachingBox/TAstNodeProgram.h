#ifndef _TEACHING_BOX_T_AST_NODE_PROGRAM_H_
#define _TEACHING_BOX_T_AST_NODE_PROGRAM_H_

#include "TAstNode.h"

class TAstNodeProgram:public TAstNode
{
public:
	TAstNodeProgram(const std::shared_ptr<TToken> token = nullptr);
	~TAstNodeProgram();

	static const std::shared_ptr<TAstNode> GetAstNode(TLexer* const lexer, const std::shared_ptr<TToken> token);

	virtual ValueReturned Execute() const override;

	virtual void ParseSemantic() const override;

	void SetId(int id);
	int GetId() const;

private:
	int m_id = 0;	/*当前程序id，可用于根据id来识别程序*/
};

#endif